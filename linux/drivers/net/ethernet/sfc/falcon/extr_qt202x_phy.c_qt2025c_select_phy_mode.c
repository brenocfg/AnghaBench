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
typedef  int uint16_t ;
struct qt202x_phy_data {int firmware_ver; } ;
struct falcon_board {scalar_t__ major; int minor; } ;
struct ef4_nic {scalar_t__ loopback_mode; int /*<<< orphan*/  net_dev; struct qt202x_phy_data* phy_data; } ;

/* Variables and functions */
 scalar_t__ LOOPBACK_NONE ; 
 int /*<<< orphan*/  PMA_PMD_MODE_REG ; 
 int PMA_PMD_RXIN_SEL_LBN ; 
 int ef4_mdio_read (struct ef4_nic*,int,int) ; 
 int /*<<< orphan*/  ef4_mdio_set_flag (struct ef4_nic*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ef4_mdio_write (struct ef4_nic*,int,int,int) ; 
 struct falcon_board* falcon_board (struct ef4_nic*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qt2025c_restart_firmware (struct ef4_nic*) ; 
 int qt2025c_wait_reset (struct ef4_nic*) ; 

__attribute__((used)) static int qt2025c_select_phy_mode(struct ef4_nic *efx)
{
	struct qt202x_phy_data *phy_data = efx->phy_data;
	struct falcon_board *board = falcon_board(efx);
	int reg, rc, i;
	uint16_t phy_op_mode;

	/* Only 2.0.1.0+ PHY firmware supports the more optimal SFP+
	 * Self-Configure mode.  Don't attempt any switching if we encounter
	 * older firmware. */
	if (phy_data->firmware_ver < 0x02000100)
		return 0;

	/* In general we will get optimal behaviour in "SFP+ Self-Configure"
	 * mode; however, that powers down most of the PHY when no module is
	 * present, so we must use a different mode (any fixed mode will do)
	 * to be sure that loopbacks will work. */
	phy_op_mode = (efx->loopback_mode == LOOPBACK_NONE) ? 0x0038 : 0x0020;

	/* Only change mode if really necessary */
	reg = ef4_mdio_read(efx, 1, 0xc319);
	if ((reg & 0x0038) == phy_op_mode)
		return 0;
	netif_dbg(efx, hw, efx->net_dev, "Switching PHY to mode 0x%04x\n",
		  phy_op_mode);

	/* This sequence replicates the register writes configured in the boot
	 * EEPROM (including the differences between board revisions), except
	 * that the operating mode is changed, and the PHY is prevented from
	 * unnecessarily reloading the main firmware image again. */
	ef4_mdio_write(efx, 1, 0xc300, 0x0000);
	/* (Note: this portion of the boot EEPROM sequence, which bit-bashes 9
	 * STOPs onto the firmware/module I2C bus to reset it, varies across
	 * board revisions, as the bus is connected to different GPIO/LED
	 * outputs on the PHY.) */
	if (board->major == 0 && board->minor < 2) {
		ef4_mdio_write(efx, 1, 0xc303, 0x4498);
		for (i = 0; i < 9; i++) {
			ef4_mdio_write(efx, 1, 0xc303, 0x4488);
			ef4_mdio_write(efx, 1, 0xc303, 0x4480);
			ef4_mdio_write(efx, 1, 0xc303, 0x4490);
			ef4_mdio_write(efx, 1, 0xc303, 0x4498);
		}
	} else {
		ef4_mdio_write(efx, 1, 0xc303, 0x0920);
		ef4_mdio_write(efx, 1, 0xd008, 0x0004);
		for (i = 0; i < 9; i++) {
			ef4_mdio_write(efx, 1, 0xc303, 0x0900);
			ef4_mdio_write(efx, 1, 0xd008, 0x0005);
			ef4_mdio_write(efx, 1, 0xc303, 0x0920);
			ef4_mdio_write(efx, 1, 0xd008, 0x0004);
		}
		ef4_mdio_write(efx, 1, 0xc303, 0x4900);
	}
	ef4_mdio_write(efx, 1, 0xc303, 0x4900);
	ef4_mdio_write(efx, 1, 0xc302, 0x0004);
	ef4_mdio_write(efx, 1, 0xc316, 0x0013);
	ef4_mdio_write(efx, 1, 0xc318, 0x0054);
	ef4_mdio_write(efx, 1, 0xc319, phy_op_mode);
	ef4_mdio_write(efx, 1, 0xc31a, 0x0098);
	ef4_mdio_write(efx, 3, 0x0026, 0x0e00);
	ef4_mdio_write(efx, 3, 0x0027, 0x0013);
	ef4_mdio_write(efx, 3, 0x0028, 0xa528);
	ef4_mdio_write(efx, 1, 0xd006, 0x000a);
	ef4_mdio_write(efx, 1, 0xd007, 0x0009);
	ef4_mdio_write(efx, 1, 0xd008, 0x0004);
	/* This additional write is not present in the boot EEPROM.  It
	 * prevents the PHY's internal boot ROM doing another pointless (and
	 * slow) reload of the firmware image (the microcontroller's code
	 * memory is not affected by the microcontroller reset). */
	ef4_mdio_write(efx, 1, 0xc317, 0x00ff);
	/* PMA/PMD loopback sets RXIN to inverse polarity and the firmware
	 * restart doesn't reset it. We need to do that ourselves. */
	ef4_mdio_set_flag(efx, 1, PMA_PMD_MODE_REG,
			  1 << PMA_PMD_RXIN_SEL_LBN, false);
	ef4_mdio_write(efx, 1, 0xc300, 0x0002);
	msleep(20);

	/* Restart microcontroller execution of firmware from RAM */
	qt2025c_restart_firmware(efx);

	/* Wait for the microcontroller to be ready again */
	rc = qt2025c_wait_reset(efx);
	if (rc < 0) {
		netif_err(efx, hw, efx->net_dev,
			  "PHY microcontroller reset during mode switch "
			  "timed out\n");
		return rc;
	}

	return 0;
}