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
struct mei_device {int /*<<< orphan*/  device_lock; } ;
struct mei_cl_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  me_cl; struct mei_cl* cl; struct mei_device* bus; } ;
struct mei_cl {scalar_t__ state; struct mei_cl_device* cldev; } ;

/* Variables and functions */
 int ENOTTY ; 
 scalar_t__ MEI_FILE_UNINITIALIZED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mei_cl_connect (struct mei_cl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mei_cl_is_connected (struct mei_cl*) ; 
 int mei_cl_link (struct mei_cl*) ; 
 int /*<<< orphan*/  mei_me_cl_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mei_cldev_enable(struct mei_cl_device *cldev)
{
	struct mei_device *bus = cldev->bus;
	struct mei_cl *cl;
	int ret;

	cl = cldev->cl;

	mutex_lock(&bus->device_lock);
	if (cl->state == MEI_FILE_UNINITIALIZED) {
		ret = mei_cl_link(cl);
		if (ret)
			goto out;
		/* update pointers */
		cl->cldev = cldev;
	}

	if (mei_cl_is_connected(cl)) {
		ret = 0;
		goto out;
	}

	if (!mei_me_cl_is_active(cldev->me_cl)) {
		dev_err(&cldev->dev, "me client is not active\n");
		ret = -ENOTTY;
		goto out;
	}

	ret = mei_cl_connect(cl, cldev->me_cl, NULL);
	if (ret < 0)
		dev_err(&cldev->dev, "cannot connect\n");

out:
	mutex_unlock(&bus->device_lock);

	return ret;
}