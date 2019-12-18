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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  DSA_PORT_REGISTER 129 
#define  DSA_PORT_UNREGISTER 128 
 int NOTIFY_DONE ; 
 int bcm_sysport_map_queues (struct notifier_block*,void*) ; 
 int bcm_sysport_unmap_queues (struct notifier_block*,void*) ; 
 int notifier_from_errno (int) ; 

__attribute__((used)) static int bcm_sysport_dsa_notifier(struct notifier_block *nb,
				    unsigned long event, void *ptr)
{
	int ret = NOTIFY_DONE;

	switch (event) {
	case DSA_PORT_REGISTER:
		ret = bcm_sysport_map_queues(nb, ptr);
		break;
	case DSA_PORT_UNREGISTER:
		ret = bcm_sysport_unmap_queues(nb, ptr);
		break;
	}

	return notifier_from_errno(ret);
}