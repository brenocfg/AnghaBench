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

__attribute__((used)) static int fnic_dev_wait(struct vnic_dev *vdev,
			 int (*start)(struct vnic_dev *, int),
			 int (*finished)(struct vnic_dev *, int *),
			 int arg)
{
	unsigned long time;
	int done;
	int err;
	int count;

	count = 0;

	err = start(vdev, arg);
	if (err)
		return err;

	/* Wait for func to complete.
	* Sometime schedule_timeout_uninterruptible take long time
	* to wake up so we do not retry as we are only waiting for
	* 2 seconds in while loop. By adding count, we make sure
	* we try atleast three times before returning -ETIMEDOUT
	*/
	time = jiffies + (HZ * 2);
	do {
		err = finished(vdev, &done);
		count++;
		if (err)
			return err;
		if (done)
			return 0;
		schedule_timeout_uninterruptible(HZ / 10);
	} while (time_after(time, jiffies) || (count < 3));

	return -ETIMEDOUT;
}