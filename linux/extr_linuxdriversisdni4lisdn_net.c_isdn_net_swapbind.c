#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ next; TYPE_1__* local; } ;
typedef  TYPE_2__ isdn_net_dev ;
struct TYPE_6__ {TYPE_2__* netdev; } ;
struct TYPE_4__ {int pre_device; int pre_channel; } ;

/* Variables and functions */
 TYPE_3__* dev ; 

__attribute__((used)) static void
isdn_net_swapbind(int drvidx)
{
	isdn_net_dev *p;

#ifdef ISDN_DEBUG_NET_ICALL
	printk(KERN_DEBUG "n_fi: swapping ch of %d\n", drvidx);
#endif
	p = dev->netdev;
	while (p) {
		if (p->local->pre_device == drvidx)
			switch (p->local->pre_channel) {
			case 0:
				p->local->pre_channel = 1;
				break;
			case 1:
				p->local->pre_channel = 0;
				break;
			}
		p = (isdn_net_dev *) p->next;
	}
}