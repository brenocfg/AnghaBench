#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ei_device {scalar_t__ mem; } ;
struct ax_device {TYPE_1__* plat; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpoc_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_GPOC_PPDSET ; 
 scalar_t__ EI_SHIFT (int) ; 
 int /*<<< orphan*/  ei_outb (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 

__attribute__((used)) static void ax_phy_switch(struct net_device *dev, int on)
{
	struct ei_device *ei_local = netdev_priv(dev);
	struct ax_device *ax = to_ax_dev(dev);

	u8 reg_gpoc =  ax->plat->gpoc_val;

	if (!!on)
		reg_gpoc &= ~AX_GPOC_PPDSET;
	else
		reg_gpoc |= AX_GPOC_PPDSET;

	ei_outb(reg_gpoc, ei_local->mem + EI_SHIFT(0x17));
}