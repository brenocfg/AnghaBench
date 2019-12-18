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
struct siox_master {int /*<<< orphan*/  poll_thread; int /*<<< orphan*/  dev; scalar_t__ active; int /*<<< orphan*/  busno; int /*<<< orphan*/  last_poll; int /*<<< orphan*/  devices; int /*<<< orphan*/  lock; int /*<<< orphan*/  pushpull; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct siox_master*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siox_is_registered ; 
 int /*<<< orphan*/  siox_poll_thread ; 

int siox_master_register(struct siox_master *smaster)
{
	int ret;

	if (!siox_is_registered)
		return -EPROBE_DEFER;

	if (!smaster->pushpull)
		return -EINVAL;

	dev_set_name(&smaster->dev, "siox-%d", smaster->busno);

	mutex_init(&smaster->lock);
	INIT_LIST_HEAD(&smaster->devices);

	smaster->last_poll = jiffies;
	smaster->poll_thread = kthread_run(siox_poll_thread, smaster,
					   "siox-%d", smaster->busno);
	if (IS_ERR(smaster->poll_thread)) {
		smaster->active = 0;
		return PTR_ERR(smaster->poll_thread);
	}

	ret = device_add(&smaster->dev);
	if (ret)
		kthread_stop(smaster->poll_thread);

	return ret;
}