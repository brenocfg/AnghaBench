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
typedef  int /*<<< orphan*/  u32 ;
struct sja1000_priv {struct kvaser_pci* priv; } ;
struct net_device {int dummy; } ;
struct kvaser_pci {scalar_t__ conf_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTCSR_ADDON_INTENABLE_M ; 
 scalar_t__ S5920_INTCSR ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void kvaser_pci_disable_irq(struct net_device *dev)
{
	struct sja1000_priv *priv = netdev_priv(dev);
	struct kvaser_pci *board = priv->priv;
	u32 intcsr;

	/* Disable interrupts from card */
	intcsr = ioread32(board->conf_addr + S5920_INTCSR);
	intcsr &= ~INTCSR_ADDON_INTENABLE_M;
	iowrite32(intcsr, board->conf_addr + S5920_INTCSR);
}