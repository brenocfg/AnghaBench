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
struct net_device {int flags; int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_3__ {int config1; int config2; int command; } ;
struct TYPE_4__ {int rx_head; TYPE_1__ regs; } ;

/* Variables and functions */
 int CFG1_BUFSELSTAT0 ; 
 int CFG1_DMABURST8 ; 
 int CFG1_LOCBUFMEM ; 
 int CFG1_RECVCOMPSTAT0 ; 
 int CFG1_RECVPROMISC ; 
 int CFG1_RECVSPECBRMULTI ; 
 int CFG1_RECVSPECBROAD ; 
 int CFG1_TRANSEND ; 
 int CFG2_CTRLO ; 
 int CFG2_ERRENCRC ; 
 int CFG2_RECVCRC ; 
 int IFF_MULTICAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  REG_BUFWIN ; 
 int /*<<< orphan*/  REG_COMMAND ; 
 int /*<<< orphan*/  REG_CONFIG1 ; 
 int /*<<< orphan*/  REG_CONFIG2 ; 
 int /*<<< orphan*/  REG_RECVEND ; 
 int /*<<< orphan*/  REG_RECVPTR ; 
 int /*<<< orphan*/  REG_TRANSMITPTR ; 
 int TX_END ; 
 int /*<<< orphan*/  buffer_write ; 
 int /*<<< orphan*/  ether3_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_outw (int,int /*<<< orphan*/ ) ; 
 int ether3_ramtest (struct net_device*,int) ; 
 int /*<<< orphan*/  ether3_setbuffer (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_writelong (struct net_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__* priv (struct net_device*) ; 

__attribute__((used)) static int ether3_init_2(struct net_device *dev)
{
	int i;

	priv(dev)->regs.config1 = CFG1_RECVCOMPSTAT0|CFG1_DMABURST8;
	priv(dev)->regs.config2 = CFG2_CTRLO|CFG2_RECVCRC|CFG2_ERRENCRC;
	priv(dev)->regs.command = 0;

	/*
	 * Set up our hardware address
	 */
	ether3_outw(priv(dev)->regs.config1 | CFG1_BUFSELSTAT0, REG_CONFIG1);
	for (i = 0; i < 6; i++)
		ether3_outb(dev->dev_addr[i], REG_BUFWIN);

	if (dev->flags & IFF_PROMISC)
		priv(dev)->regs.config1 |= CFG1_RECVPROMISC;
	else if (dev->flags & IFF_MULTICAST)
		priv(dev)->regs.config1 |= CFG1_RECVSPECBRMULTI;
	else
		priv(dev)->regs.config1 |= CFG1_RECVSPECBROAD;

	/*
	 * There is a problem with the NQ8005 in that it occasionally loses the
	 * last two bytes.  To get round this problem, we receive the CRC as
	 * well.  That way, if we do lose the last two, then it doesn't matter.
	 */
	ether3_outw(priv(dev)->regs.config1 | CFG1_TRANSEND, REG_CONFIG1);
	ether3_outw((TX_END>>8) - 1, REG_BUFWIN);
	ether3_outw(priv(dev)->rx_head, REG_RECVPTR);
	ether3_outw(0, REG_TRANSMITPTR);
	ether3_outw(priv(dev)->rx_head >> 8, REG_RECVEND);
	ether3_outw(priv(dev)->regs.config2, REG_CONFIG2);
	ether3_outw(priv(dev)->regs.config1 | CFG1_LOCBUFMEM, REG_CONFIG1);
	ether3_outw(priv(dev)->regs.command, REG_COMMAND);

	i = ether3_ramtest(dev, 0x5A);
	if(i)
		return i;
	i = ether3_ramtest(dev, 0x1E);
	if(i)
		return i;

	ether3_setbuffer(dev, buffer_write, 0);
	ether3_writelong(dev, 0);
	return 0;
}