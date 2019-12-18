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
struct net_device {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {scalar_t__ command; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;

/* Variables and functions */
 int CMD_RXOFF ; 
 int CMD_TXOFF ; 
 int /*<<< orphan*/  REG_COMMAND ; 
 scalar_t__ REG_CONFIG2 ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int STAT_RXON ; 
 int STAT_TXON ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int ether3_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_outb (int,scalar_t__) ; 
 int /*<<< orphan*/  ether3_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 TYPE_2__* priv (struct net_device*) ; 

__attribute__((used)) static int
ether3_close(struct net_device *dev)
{
	netif_stop_queue(dev);

	disable_irq(dev->irq);

	ether3_outw(CMD_RXOFF|CMD_TXOFF, REG_COMMAND);
	priv(dev)->regs.command = 0;
	while (ether3_inw(REG_STATUS) & (STAT_RXON|STAT_TXON))
		barrier();
	ether3_outb(0x80, REG_CONFIG2 + 4);
	ether3_outw(0, REG_COMMAND);

	free_irq(dev->irq, dev);

	return 0;
}