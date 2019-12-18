#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_3__ {int command; int config1; int config2; } ;
struct TYPE_4__ {int rx_head; TYPE_1__ regs; scalar_t__ tx_tail; scalar_t__ tx_head; } ;

/* Variables and functions */
 int CFG1_BUFSELSTAT0 ; 
 int CFG1_LOCBUFMEM ; 
 int CFG1_TRANSEND ; 
 int CFG2_CTRLO ; 
 int CFG2_RESET ; 
 int CMD_ENINTRX ; 
 int CMD_ENINTTX ; 
 int CMD_RXOFF ; 
 int CMD_RXON ; 
 int CMD_TXOFF ; 
 int /*<<< orphan*/  REG_BUFWIN ; 
 int /*<<< orphan*/  REG_COMMAND ; 
 int /*<<< orphan*/  REG_CONFIG1 ; 
 int /*<<< orphan*/  REG_CONFIG2 ; 
 int /*<<< orphan*/  REG_RECVEND ; 
 int /*<<< orphan*/  REG_RECVPTR ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int /*<<< orphan*/  REG_TRANSMITPTR ; 
 int RX_START ; 
 int STAT_RXON ; 
 int STAT_TXON ; 
 int TX_END ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  buffer_write ; 
 int ether3_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_setbuffer (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_writelong (struct net_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__* priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
ether3_init_for_open(struct net_device *dev)
{
	int i;

	/* Reset the chip */
	ether3_outw(CFG2_RESET, REG_CONFIG2);
	udelay(4);

	priv(dev)->regs.command = 0;
	ether3_outw(CMD_RXOFF|CMD_TXOFF, REG_COMMAND);
	while (ether3_inw(REG_STATUS) & (STAT_RXON|STAT_TXON))
		barrier();

	ether3_outw(priv(dev)->regs.config1 | CFG1_BUFSELSTAT0, REG_CONFIG1);
	for (i = 0; i < 6; i++)
		ether3_outb(dev->dev_addr[i], REG_BUFWIN);

	priv(dev)->tx_head	= 0;
	priv(dev)->tx_tail	= 0;
	priv(dev)->regs.config2 |= CFG2_CTRLO;
	priv(dev)->rx_head	= RX_START;

	ether3_outw(priv(dev)->regs.config1 | CFG1_TRANSEND, REG_CONFIG1);
	ether3_outw((TX_END>>8) - 1, REG_BUFWIN);
	ether3_outw(priv(dev)->rx_head, REG_RECVPTR);
	ether3_outw(priv(dev)->rx_head >> 8, REG_RECVEND);
	ether3_outw(0, REG_TRANSMITPTR);
	ether3_outw(priv(dev)->regs.config2, REG_CONFIG2);
	ether3_outw(priv(dev)->regs.config1 | CFG1_LOCBUFMEM, REG_CONFIG1);

	ether3_setbuffer(dev, buffer_write, 0);
	ether3_writelong(dev, 0);

	priv(dev)->regs.command = CMD_ENINTRX | CMD_ENINTTX;
	ether3_outw(priv(dev)->regs.command | CMD_RXON, REG_COMMAND);
}