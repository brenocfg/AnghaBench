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
struct tcmu_dev {int /*<<< orphan*/  cmdr_lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCMU_DEV_BIT_BLOCKED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_qfull_queue (struct tcmu_dev*,int) ; 
 int /*<<< orphan*/  tcmu_handle_completions (struct tcmu_dev*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcmu_block_dev(struct tcmu_dev *udev)
{
	mutex_lock(&udev->cmdr_lock);

	if (test_and_set_bit(TCMU_DEV_BIT_BLOCKED, &udev->flags))
		goto unlock;

	/* complete IO that has executed successfully */
	tcmu_handle_completions(udev);
	/* fail IO waiting to be queued */
	run_qfull_queue(udev, true);

unlock:
	mutex_unlock(&udev->cmdr_lock);
}