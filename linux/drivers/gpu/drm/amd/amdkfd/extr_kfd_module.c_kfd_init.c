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
 int EINVAL ; 
 int KFD_MAX_NUM_OF_QUEUES_PER_DEVICE ; 
 scalar_t__ KFD_SCHED_POLICY_HWS ; 
 scalar_t__ KFD_SCHED_POLICY_NO_HWS ; 
 int /*<<< orphan*/  kfd_chardev_exit () ; 
 int kfd_chardev_init () ; 
 int /*<<< orphan*/  kfd_debugfs_init () ; 
 int kfd_process_create_wq () ; 
 int /*<<< orphan*/  kfd_procfs_init () ; 
 int kfd_topology_init () ; 
 int /*<<< orphan*/  kfd_topology_shutdown () ; 
 int max_num_of_queues_per_device ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ sched_policy ; 

__attribute__((used)) static int kfd_init(void)
{
	int err;

	/* Verify module parameters */
	if ((sched_policy < KFD_SCHED_POLICY_HWS) ||
		(sched_policy > KFD_SCHED_POLICY_NO_HWS)) {
		pr_err("sched_policy has invalid value\n");
		return -EINVAL;
	}

	/* Verify module parameters */
	if ((max_num_of_queues_per_device < 1) ||
		(max_num_of_queues_per_device >
			KFD_MAX_NUM_OF_QUEUES_PER_DEVICE)) {
		pr_err("max_num_of_queues_per_device must be between 1 to KFD_MAX_NUM_OF_QUEUES_PER_DEVICE\n");
		return -EINVAL;
	}

	err = kfd_chardev_init();
	if (err < 0)
		goto err_ioctl;

	err = kfd_topology_init();
	if (err < 0)
		goto err_topology;

	err = kfd_process_create_wq();
	if (err < 0)
		goto err_create_wq;

	/* Ignore the return value, so that we can continue
	 * to init the KFD, even if procfs isn't craated
	 */
	kfd_procfs_init();

	kfd_debugfs_init();

	return 0;

err_create_wq:
	kfd_topology_shutdown();
err_topology:
	kfd_chardev_exit();
err_ioctl:
	return err;
}