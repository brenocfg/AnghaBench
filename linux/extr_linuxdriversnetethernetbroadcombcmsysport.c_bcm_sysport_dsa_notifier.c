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
struct dsa_notifier_register_info {int dummy; } ;

/* Variables and functions */
 unsigned long DSA_PORT_REGISTER ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  bcm_sysport_map_queues (struct notifier_block*,struct dsa_notifier_register_info*) ; 
 int notifier_from_errno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sysport_dsa_notifier(struct notifier_block *nb,
				    unsigned long event, void *ptr)
{
	struct dsa_notifier_register_info *info;

	if (event != DSA_PORT_REGISTER)
		return NOTIFY_DONE;

	info = ptr;

	return notifier_from_errno(bcm_sysport_map_queues(nb, info));
}