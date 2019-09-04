#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  devt; } ;
struct mousedev {TYPE_1__ dev; int /*<<< orphan*/  handle; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  input_free_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mousedev_cleanup (struct mousedev*) ; 
 struct mousedev* mousedev_mix ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static void mousedev_destroy(struct mousedev *mousedev)
{
	cdev_device_del(&mousedev->cdev, &mousedev->dev);
	mousedev_cleanup(mousedev);
	input_free_minor(MINOR(mousedev->dev.devt));
	if (mousedev != mousedev_mix)
		input_unregister_handle(&mousedev->handle);
	put_device(&mousedev->dev);
}