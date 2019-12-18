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
typedef  int u_int ;
struct net_device {int base_addr; int /*<<< orphan*/  name; } ;
struct hp100_private {int mode; } ;

/* Variables and functions */
 int HP100_HW_RST ; 
 int HP100_INT_EN ; 
 int HP100_MMAP_DIS ; 
 int HP100_RESET_LB ; 
 int HP100_RX_EN ; 
 int HP100_RX_IDLE ; 
 int HP100_SET_HB ; 
 int HP100_TRI_INT ; 
 int HP100_TX_EN ; 
 int HP100_TX_IDLE ; 
 int /*<<< orphan*/  MAC_CFG_1 ; 
 int /*<<< orphan*/  MAC_CTRL ; 
 int /*<<< orphan*/  OPTION_LSW ; 
 int /*<<< orphan*/  PERFORMANCE ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  hp100_BM_shutdown (struct net_device*) ; 
 int /*<<< orphan*/  hp100_andb (int,int /*<<< orphan*/ ) ; 
 int hp100_inb (int /*<<< orphan*/ ) ; 
 int hp100_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_page (int /*<<< orphan*/ ) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hp100_stop_interface(struct net_device *dev)
{
	struct hp100_private *lp = netdev_priv(dev);
	int ioaddr = dev->base_addr;
	u_int val;

#ifdef HP100_DEBUG_B
	printk("hp100: %s: hp100_stop_interface\n", dev->name);
	hp100_outw(0x4221, TRACE);
#endif

	if (lp->mode == 1)
		hp100_BM_shutdown(dev);
	else {
		/* Note: MMAP_DIS will be reenabled by start_interface */
		hp100_outw(HP100_INT_EN | HP100_RESET_LB |
			   HP100_TRI_INT | HP100_MMAP_DIS | HP100_SET_HB,
			   OPTION_LSW);
		val = hp100_inw(OPTION_LSW);

		hp100_page(MAC_CTRL);
		hp100_andb(~(HP100_RX_EN | HP100_TX_EN), MAC_CFG_1);

		if (!(val & HP100_HW_RST))
			return;	/* If reset, imm. return ... */
		/* ... else: busy wait until idle */
		for (val = 0; val < 6000; val++)
			if ((hp100_inb(MAC_CFG_1) & (HP100_TX_IDLE | HP100_RX_IDLE)) == (HP100_TX_IDLE | HP100_RX_IDLE)) {
				hp100_page(PERFORMANCE);
				return;
			}
		printk("hp100: %s: hp100_stop_interface - timeout\n", dev->name);
		hp100_page(PERFORMANCE);
	}
}