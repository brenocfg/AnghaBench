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

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FW_FEATURE_CMO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmm_dev ; 
 scalar_t__ cmm_disabled ; 
 int /*<<< orphan*/  cmm_mem_isolate_nb ; 
 int /*<<< orphan*/  cmm_mem_nb ; 
 int /*<<< orphan*/  cmm_oom_nb ; 
 int /*<<< orphan*/  cmm_reboot_nb ; 
 int cmm_sysfs_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmm_thread ; 
 int /*<<< orphan*/  cmm_thread_ptr ; 
 int /*<<< orphan*/  cmm_unregister_sysfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ register_memory_isolate_notifier (int /*<<< orphan*/ *) ; 
 scalar_t__ register_memory_notifier (int /*<<< orphan*/ *) ; 
 int register_oom_notifier (int /*<<< orphan*/ *) ; 
 int register_reboot_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_memory_isolate_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_memory_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_oom_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmm_init(void)
{
	int rc = -ENOMEM;

	if (!firmware_has_feature(FW_FEATURE_CMO))
		return -EOPNOTSUPP;

	if ((rc = register_oom_notifier(&cmm_oom_nb)) < 0)
		return rc;

	if ((rc = register_reboot_notifier(&cmm_reboot_nb)))
		goto out_oom_notifier;

	if ((rc = cmm_sysfs_register(&cmm_dev)))
		goto out_reboot_notifier;

	if (register_memory_notifier(&cmm_mem_nb) ||
	    register_memory_isolate_notifier(&cmm_mem_isolate_nb))
		goto out_unregister_notifier;

	if (cmm_disabled)
		return rc;

	cmm_thread_ptr = kthread_run(cmm_thread, NULL, "cmmthread");
	if (IS_ERR(cmm_thread_ptr)) {
		rc = PTR_ERR(cmm_thread_ptr);
		goto out_unregister_notifier;
	}

	return rc;

out_unregister_notifier:
	unregister_memory_notifier(&cmm_mem_nb);
	unregister_memory_isolate_notifier(&cmm_mem_isolate_nb);
	cmm_unregister_sysfs(&cmm_dev);
out_reboot_notifier:
	unregister_reboot_notifier(&cmm_reboot_nb);
out_oom_notifier:
	unregister_oom_notifier(&cmm_oom_nb);
	return rc;
}