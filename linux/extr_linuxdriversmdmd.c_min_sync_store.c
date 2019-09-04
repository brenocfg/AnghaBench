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
struct mddev {unsigned long long resync_max; int /*<<< orphan*/  lock; int /*<<< orphan*/  resync_min; int /*<<< orphan*/  recovery; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  MD_RECOVERY_RUNNING ; 
 scalar_t__ kstrtoull (char const*,int,unsigned long long*) ; 
 int /*<<< orphan*/  round_down (unsigned long long,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
min_sync_store(struct mddev *mddev, const char *buf, size_t len)
{
	unsigned long long min;
	int err;

	if (kstrtoull(buf, 10, &min))
		return -EINVAL;

	spin_lock(&mddev->lock);
	err = -EINVAL;
	if (min > mddev->resync_max)
		goto out_unlock;

	err = -EBUSY;
	if (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		goto out_unlock;

	/* Round down to multiple of 4K for safety */
	mddev->resync_min = round_down(min, 8);
	err = 0;

out_unlock:
	spin_unlock(&mddev->lock);
	return err ?: len;
}