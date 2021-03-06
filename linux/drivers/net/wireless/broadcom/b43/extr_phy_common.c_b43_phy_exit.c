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
struct TYPE_2__ {int do_full_init; struct b43_phy_operations* ops; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_operations {int /*<<< orphan*/  (* exit ) (struct b43_wldev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  b43_software_rfkill (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  stub1 (struct b43_wldev*) ; 

void b43_phy_exit(struct b43_wldev *dev)
{
	const struct b43_phy_operations *ops = dev->phy.ops;

	b43_software_rfkill(dev, true);
	dev->phy.do_full_init = true;
	if (ops->exit)
		ops->exit(dev);
}