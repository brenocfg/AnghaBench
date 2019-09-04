#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct e1000_hw {int mac_type; int tbi_compatibility_on; int pci_cmd_word; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_DUP ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CTRL_EXT_EE_RST ; 
 int E1000_CTRL_PHY_RST ; 
 int E1000_CTRL_RST ; 
 int E1000_MANC_ARP_EN ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int E1000_TCTL_PSP ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  E1000_WRITE_REG_IO (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ICR ; 
 int IGP_ACTIVITY_LED_ENABLE ; 
 int IGP_ACTIVITY_LED_MASK ; 
 int IGP_LED3_MODE ; 
 int /*<<< orphan*/  IMC ; 
 int /*<<< orphan*/  LEDCTL ; 
 int /*<<< orphan*/  MANC ; 
 int PCI_COMMAND_INVALIDATE ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  TCTL ; 
#define  e1000_82540 141 
#define  e1000_82541 140 
#define  e1000_82541_rev_2 139 
#define  e1000_82542_rev2_0 138 
#define  e1000_82542_rev2_1 137 
#define  e1000_82543 136 
#define  e1000_82544 135 
#define  e1000_82545 134 
#define  e1000_82545_rev_3 133 
#define  e1000_82546 132 
#define  e1000_82546_rev_3 131 
#define  e1000_82547 130 
#define  e1000_82547_rev_2 129 
#define  e1000_ce4100 128 
 int /*<<< orphan*/  e1000_get_auto_rd_done (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_pci_clear_mwi (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_pci_set_mwi (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_phy_init_script (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 e1000_reset_hw(struct e1000_hw *hw)
{
	u32 ctrl;
	u32 ctrl_ext;
	u32 icr;
	u32 manc;
	u32 led_ctrl;
	s32 ret_val;

	/* For 82542 (rev 2.0), disable MWI before issuing a device reset */
	if (hw->mac_type == e1000_82542_rev2_0) {
		e_dbg("Disabling MWI on 82542 rev 2.0\n");
		e1000_pci_clear_mwi(hw);
	}

	/* Clear interrupt mask to stop board from generating interrupts */
	e_dbg("Masking off all interrupts\n");
	ew32(IMC, 0xffffffff);

	/* Disable the Transmit and Receive units.  Then delay to allow
	 * any pending transactions to complete before we hit the MAC with
	 * the global reset.
	 */
	ew32(RCTL, 0);
	ew32(TCTL, E1000_TCTL_PSP);
	E1000_WRITE_FLUSH();

	/* The tbi_compatibility_on Flag must be cleared when Rctl is cleared. */
	hw->tbi_compatibility_on = false;

	/* Delay to allow any outstanding PCI transactions to complete before
	 * resetting the device
	 */
	msleep(10);

	ctrl = er32(CTRL);

	/* Must reset the PHY before resetting the MAC */
	if ((hw->mac_type == e1000_82541) || (hw->mac_type == e1000_82547)) {
		ew32(CTRL, (ctrl | E1000_CTRL_PHY_RST));
		E1000_WRITE_FLUSH();
		msleep(5);
	}

	/* Issue a global reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA, and link units.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	e_dbg("Issuing a global reset to MAC\n");

	switch (hw->mac_type) {
	case e1000_82544:
	case e1000_82540:
	case e1000_82545:
	case e1000_82546:
	case e1000_82541:
	case e1000_82541_rev_2:
		/* These controllers can't ack the 64-bit write when issuing the
		 * reset, so use IO-mapping as a workaround to issue the reset
		 */
		E1000_WRITE_REG_IO(hw, CTRL, (ctrl | E1000_CTRL_RST));
		break;
	case e1000_82545_rev_3:
	case e1000_82546_rev_3:
		/* Reset is performed on a shadow of the control register */
		ew32(CTRL_DUP, (ctrl | E1000_CTRL_RST));
		break;
	case e1000_ce4100:
	default:
		ew32(CTRL, (ctrl | E1000_CTRL_RST));
		break;
	}

	/* After MAC reset, force reload of EEPROM to restore power-on settings
	 * to device.  Later controllers reload the EEPROM automatically, so
	 * just wait for reload to complete.
	 */
	switch (hw->mac_type) {
	case e1000_82542_rev2_0:
	case e1000_82542_rev2_1:
	case e1000_82543:
	case e1000_82544:
		/* Wait for reset to complete */
		udelay(10);
		ctrl_ext = er32(CTRL_EXT);
		ctrl_ext |= E1000_CTRL_EXT_EE_RST;
		ew32(CTRL_EXT, ctrl_ext);
		E1000_WRITE_FLUSH();
		/* Wait for EEPROM reload */
		msleep(2);
		break;
	case e1000_82541:
	case e1000_82541_rev_2:
	case e1000_82547:
	case e1000_82547_rev_2:
		/* Wait for EEPROM reload */
		msleep(20);
		break;
	default:
		/* Auto read done will delay 5ms or poll based on mac type */
		ret_val = e1000_get_auto_rd_done(hw);
		if (ret_val)
			return ret_val;
		break;
	}

	/* Disable HW ARPs on ASF enabled adapters */
	if (hw->mac_type >= e1000_82540) {
		manc = er32(MANC);
		manc &= ~(E1000_MANC_ARP_EN);
		ew32(MANC, manc);
	}

	if ((hw->mac_type == e1000_82541) || (hw->mac_type == e1000_82547)) {
		e1000_phy_init_script(hw);

		/* Configure activity LED after PHY reset */
		led_ctrl = er32(LEDCTL);
		led_ctrl &= IGP_ACTIVITY_LED_MASK;
		led_ctrl |= (IGP_ACTIVITY_LED_ENABLE | IGP_LED3_MODE);
		ew32(LEDCTL, led_ctrl);
	}

	/* Clear interrupt mask to stop board from generating interrupts */
	e_dbg("Masking off all interrupts\n");
	ew32(IMC, 0xffffffff);

	/* Clear any pending interrupt events. */
	icr = er32(ICR);

	/* If MWI was previously enabled, reenable it. */
	if (hw->mac_type == e1000_82542_rev2_0) {
		if (hw->pci_cmd_word & PCI_COMMAND_INVALIDATE)
			e1000_pci_set_mwi(hw);
	}

	return E1000_SUCCESS;
}