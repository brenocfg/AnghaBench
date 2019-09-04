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
struct TYPE_2__ {int* usage; } ;

/* Variables and functions */
 int ISDN_USAGE_EXCLUSIVE ; 
 TYPE_1__* dev ; 
 int /*<<< orphan*/  isdn_info_update () ; 

__attribute__((used)) static void
isdn_net_swap_usage(int i1, int i2)
{
	int u1 = dev->usage[i1] & ISDN_USAGE_EXCLUSIVE;
	int u2 = dev->usage[i2] & ISDN_USAGE_EXCLUSIVE;

#ifdef ISDN_DEBUG_NET_ICALL
	printk(KERN_DEBUG "n_fi: usage of %d and %d\n", i1, i2);
#endif
	dev->usage[i1] &= ~ISDN_USAGE_EXCLUSIVE;
	dev->usage[i1] |= u2;
	dev->usage[i2] &= ~ISDN_USAGE_EXCLUSIVE;
	dev->usage[i2] |= u1;
	isdn_info_update();
}