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
 int NOTIFY_DONE ; 
 unsigned long SYS_RESTART ; 
 int /*<<< orphan*/  kvm_pv_guest_cpu_reboot ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int kvm_pv_reboot_notify(struct notifier_block *nb,
				unsigned long code, void *unused)
{
	if (code == SYS_RESTART)
		on_each_cpu(kvm_pv_guest_cpu_reboot, NULL, 1);
	return NOTIFY_DONE;
}