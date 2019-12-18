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
struct net_device {unsigned int base_addr; int* dev_addr; } ;
struct local_info {scalar_t__ cardtype; } ;

/* Variables and functions */
 int AUTO_MODE ; 
 int BANK_0 ; 
 int BANK_0U ; 
 int BANK_2 ; 
 int BANK_2U ; 
 scalar_t__ BMPR12 ; 
 scalar_t__ BMPR13 ; 
 scalar_t__ COL_CTRL ; 
 int CONFIG0_DFL ; 
 int CONFIG0_DFL_1 ; 
 int CONFIG0_RST ; 
 int CONFIG0_RST_1 ; 
 scalar_t__ CONFIG_0 ; 
 scalar_t__ CONFIG_1 ; 
 scalar_t__ CONTEC ; 
 scalar_t__ DATAPORT ; 
 int D_RX_INTR ; 
 int D_TX_INTR ; 
 int D_TX_MODE ; 
 int ID_MATCHED ; 
 int INTR_OFF ; 
 int INTR_ON ; 
 scalar_t__ LAN_CTRL ; 
 scalar_t__ MBH10302 ; 
 scalar_t__ NODE_ID ; 
 scalar_t__ RX_INTR ; 
 scalar_t__ RX_MODE ; 
 scalar_t__ RX_SKIP ; 
 scalar_t__ RX_STATUS ; 
 scalar_t__ TDK ; 
 int TDK_AUTO_MODE ; 
 scalar_t__ TX_INTR ; 
 scalar_t__ TX_MODE ; 
 scalar_t__ TX_STATUS ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  set_rx_mode (struct net_device*) ; 
 scalar_t__ sram_config ; 

__attribute__((used)) static void fjn_reset(struct net_device *dev)
{
    struct local_info *lp = netdev_priv(dev);
    unsigned int ioaddr = dev->base_addr;
    int i;

    netdev_dbg(dev, "fjn_reset() called\n");

    /* Reset controller */
    if( sram_config == 0 ) 
	outb(CONFIG0_RST, ioaddr + CONFIG_0);
    else
	outb(CONFIG0_RST_1, ioaddr + CONFIG_0);

    /* Power On chip and select bank 0 */
    if (lp->cardtype == MBH10302)
	outb(BANK_0, ioaddr + CONFIG_1);
    else
	outb(BANK_0U, ioaddr + CONFIG_1);

    /* Set Tx modes */
    outb(D_TX_MODE, ioaddr + TX_MODE);
    /* set Rx modes */
    outb(ID_MATCHED, ioaddr + RX_MODE);

    /* Set hardware address */
    for (i = 0; i < 6; i++) 
        outb(dev->dev_addr[i], ioaddr + NODE_ID + i);

    /* (re)initialize the multicast table */
    set_rx_mode(dev);

    /* Switch to bank 2 (runtime mode) */
    if (lp->cardtype == MBH10302)
	outb(BANK_2, ioaddr + CONFIG_1);
    else
	outb(BANK_2U, ioaddr + CONFIG_1);

    /* set 16col ctrl bits */
    if( lp->cardtype == TDK || lp->cardtype == CONTEC) 
        outb(TDK_AUTO_MODE, ioaddr + COL_CTRL);
    else
        outb(AUTO_MODE, ioaddr + COL_CTRL);

    /* clear Reserved Regs */
    outb(0x00, ioaddr + BMPR12);
    outb(0x00, ioaddr + BMPR13);

    /* reset Skip packet reg. */
    outb(0x01, ioaddr + RX_SKIP);

    /* Enable Tx and Rx */
    if( sram_config == 0 )
	outb(CONFIG0_DFL, ioaddr + CONFIG_0);
    else
	outb(CONFIG0_DFL_1, ioaddr + CONFIG_0);

    /* Init receive pointer ? */
    inw(ioaddr + DATAPORT);
    inw(ioaddr + DATAPORT);

    /* Clear all status */
    outb(0xff, ioaddr + TX_STATUS);
    outb(0xff, ioaddr + RX_STATUS);

    if (lp->cardtype == MBH10302)
	outb(INTR_OFF, ioaddr + LAN_CTRL);

    /* Turn on Rx interrupts */
    outb(D_TX_INTR, ioaddr + TX_INTR);
    outb(D_RX_INTR, ioaddr + RX_INTR);

    /* Turn on interrupts from LAN card controller */
    if (lp->cardtype == MBH10302)
	outb(INTR_ON, ioaddr + LAN_CTRL);
}