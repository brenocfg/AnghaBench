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
struct net_device {int base_addr; int /*<<< orphan*/  name; } ;
struct hp100_private {int mode; scalar_t__ lan_type; } ;

/* Variables and functions */
 int HP100_ADV_NXT_PKT ; 
 int HP100_BM_READ ; 
 int HP100_BM_WRITE ; 
 int HP100_DEBUG_EN ; 
 int HP100_EE_EN ; 
 int HP100_FAKE_INT ; 
 int HP100_INT_EN ; 
 int HP100_IO_EN ; 
 scalar_t__ HP100_LAN_100 ; 
 scalar_t__ HP100_LAN_ERR ; 
 int HP100_MEM_EN ; 
 int HP100_MMAP_DIS ; 
 int HP100_PRIORITY_TX ; 
 int HP100_RESET_HB ; 
 int HP100_RESET_LB ; 
 int HP100_RX_EN ; 
 int HP100_RX_HDR ; 
 int HP100_SET_HB ; 
 int HP100_TRI_INT ; 
 int HP100_TX_CMD ; 
 int HP100_TX_EN ; 
 int /*<<< orphan*/  IRQ_MASK ; 
 int /*<<< orphan*/  IRQ_STATUS ; 
 int /*<<< orphan*/  MAC_CFG_1 ; 
 int /*<<< orphan*/  MAC_CTRL ; 
 int /*<<< orphan*/  OPTION_LSW ; 
 int /*<<< orphan*/  OPTION_MSW ; 
 int /*<<< orphan*/  PERFORMANCE ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  hp100_BM_shutdown (struct net_device*) ; 
 int /*<<< orphan*/  hp100_andb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_cascade_reset (struct net_device*,int) ; 
 int /*<<< orphan*/  hp100_load_eeprom (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_login_to_vg_hub (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_mmuinit (struct net_device*) ; 
 int /*<<< orphan*/  hp100_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_page (int /*<<< orphan*/ ) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait () ; 

__attribute__((used)) static void hp100_hwinit(struct net_device *dev)
{
	int ioaddr = dev->base_addr;
	struct hp100_private *lp = netdev_priv(dev);

#ifdef HP100_DEBUG_B
	hp100_outw(0x4202, TRACE);
	printk("hp100: %s: hwinit\n", dev->name);
#endif

	/* Initialise the card. -------------------------------------------- */

	/* Clear all pending Ints and disable Ints */
	hp100_page(PERFORMANCE);
	hp100_outw(0xfefe, IRQ_MASK);	/* mask off all ints */
	hp100_outw(0xffff, IRQ_STATUS);	/* clear all pending ints */

	hp100_outw(HP100_INT_EN | HP100_RESET_LB, OPTION_LSW);
	hp100_outw(HP100_TRI_INT | HP100_SET_HB, OPTION_LSW);

	if (lp->mode == 1) {
		hp100_BM_shutdown(dev);	/* disables BM, puts cascade in reset */
		wait();
	} else {
		hp100_outw(HP100_INT_EN | HP100_RESET_LB, OPTION_LSW);
		hp100_cascade_reset(dev, 1);
		hp100_page(MAC_CTRL);
		hp100_andb(~(HP100_RX_EN | HP100_TX_EN), MAC_CFG_1);
	}

	/* Initiate EEPROM reload */
	hp100_load_eeprom(dev, 0);

	wait();

	/* Go into reset again. */
	hp100_cascade_reset(dev, 1);

	/* Set Option Registers to a safe state  */
	hp100_outw(HP100_DEBUG_EN |
		   HP100_RX_HDR |
		   HP100_EE_EN |
		   HP100_BM_WRITE |
		   HP100_BM_READ | HP100_RESET_HB |
		   HP100_FAKE_INT |
		   HP100_INT_EN |
		   HP100_MEM_EN |
		   HP100_IO_EN | HP100_RESET_LB, OPTION_LSW);

	hp100_outw(HP100_TRI_INT |
		   HP100_MMAP_DIS | HP100_SET_HB, OPTION_LSW);

	hp100_outb(HP100_PRIORITY_TX |
		   HP100_ADV_NXT_PKT |
		   HP100_TX_CMD | HP100_RESET_LB, OPTION_MSW);

	/* TODO: Configure MMU for Ram Test. */
	/* TODO: Ram Test. */

	/* Re-check if adapter is still at same i/o location      */
	/* (If the base i/o in eeprom has been changed but the    */
	/* registers had not been changed, a reload of the eeprom */
	/* would move the adapter to the address stored in eeprom */

	/* TODO: Code to implement. */

	/* Until here it was code from HWdiscover procedure. */
	/* Next comes code from mmuinit procedure of SCO BM driver which is
	 * called from HWconfigure in the SCO driver.  */

	/* Initialise MMU, eventually switch on Busmaster Mode, initialise
	 * multicast filter...
	 */
	hp100_mmuinit(dev);

	/* We don't turn the interrupts on here - this is done by start_interface. */
	wait();			/* TODO: Do we really need this? */

	/* Enable Hardware (e.g. unreset) */
	hp100_cascade_reset(dev, 0);

	/* ------- initialisation complete ----------- */

	/* Finally try to log in the Hub if there may be a VG connection. */
	if ((lp->lan_type == HP100_LAN_100) || (lp->lan_type == HP100_LAN_ERR))
		hp100_login_to_vg_hub(dev, 0);	/* relogin */

}