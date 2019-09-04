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
 int /*<<< orphan*/  RAC_ENABLED ; 
 int /*<<< orphan*/  RAC_SUSPENDED ; 
 unsigned long SYS_RESTART ; 
 int /*<<< orphan*/  b15_rac_disable_and_flush () ; 
 int /*<<< orphan*/  b15_rac_flags ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rac_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b15_rac_reboot_notifier(struct notifier_block *nb,
				   unsigned long action,
				   void *data)
{
	/* During kexec, we are not yet migrated on the boot CPU, so we need to
	 * make sure we are SMP safe here. Once the RAC is disabled, flag it as
	 * suspended such that the hotplug notifier returns early.
	 */
	if (action == SYS_RESTART) {
		spin_lock(&rac_lock);
		b15_rac_disable_and_flush();
		clear_bit(RAC_ENABLED, &b15_rac_flags);
		set_bit(RAC_SUSPENDED, &b15_rac_flags);
		spin_unlock(&rac_lock);
	}

	return NOTIFY_DONE;
}