#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mousedev {int opened_by_mixdev; int /*<<< orphan*/  mixdev_node; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; scalar_t__ open; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* mousedev_mix ; 
 int /*<<< orphan*/  mousedev_mix_list ; 
 int mousedev_open_device (struct mousedev*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mixdev_add_device(struct mousedev *mousedev)
{
	int retval;

	retval = mutex_lock_interruptible(&mousedev_mix->mutex);
	if (retval)
		return retval;

	if (mousedev_mix->open) {
		retval = mousedev_open_device(mousedev);
		if (retval)
			goto out;

		mousedev->opened_by_mixdev = true;
	}

	get_device(&mousedev->dev);
	list_add_tail(&mousedev->mixdev_node, &mousedev_mix_list);

 out:
	mutex_unlock(&mousedev_mix->mutex);
	return retval;
}