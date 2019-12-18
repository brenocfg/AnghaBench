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
struct device {int dummy; } ;
typedef  enum nd_async_mode { ____Placeholder_nd_async_mode } nd_async_mode ;

/* Variables and functions */
#define  ND_ASYNC 129 
#define  ND_SYNC 128 
 int /*<<< orphan*/  async_schedule_domain (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int kill_device (struct device*) ; 
 int /*<<< orphan*/  nd_async_device_unregister ; 
 int /*<<< orphan*/  nd_async_domain ; 
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 int /*<<< orphan*/  nd_synchronize () ; 

void nd_device_unregister(struct device *dev, enum nd_async_mode mode)
{
	bool killed;

	switch (mode) {
	case ND_ASYNC:
		/*
		 * In the async case this is being triggered with the
		 * device lock held and the unregistration work needs to
		 * be moved out of line iff this is thread has won the
		 * race to schedule the deletion.
		 */
		if (!kill_device(dev))
			return;

		get_device(dev);
		async_schedule_domain(nd_async_device_unregister, dev,
				&nd_async_domain);
		break;
	case ND_SYNC:
		/*
		 * In the sync case the device is being unregistered due
		 * to a state change of the parent. Claim the kill state
		 * to synchronize against other unregistration requests,
		 * or otherwise let the async path handle it if the
		 * unregistration was already queued.
		 */
		nd_device_lock(dev);
		killed = kill_device(dev);
		nd_device_unlock(dev);

		if (!killed)
			return;

		nd_synchronize();
		device_unregister(dev);
		break;
	}
}