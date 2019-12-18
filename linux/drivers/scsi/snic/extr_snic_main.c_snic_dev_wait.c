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
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int jiffies ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_after (unsigned long,int) ; 

__attribute__((used)) static int
snic_dev_wait(struct vnic_dev *vdev,
		int (*start)(struct vnic_dev *, int),
		int (*finished)(struct vnic_dev *, int *),
		int arg)
{
	unsigned long time;
	int ret, done;
	int retry_cnt = 0;

	ret = start(vdev, arg);
	if (ret)
		return ret;

	/*
	 * Wait for func to complete...2 seconds max.
	 *
	 * Sometimes schedule_timeout_uninterruptible take long	time
	 * to wakeup, which results skipping retry. The retry counter
	 * ensures to retry at least two times.
	 */
	time = jiffies + (HZ * 2);
	do {
		ret = finished(vdev, &done);
		if (ret)
			return ret;

		if (done)
			return 0;
		schedule_timeout_uninterruptible(HZ/10);
		++retry_cnt;
	} while (time_after(time, jiffies) || (retry_cnt < 3));

	return -ETIMEDOUT;
}