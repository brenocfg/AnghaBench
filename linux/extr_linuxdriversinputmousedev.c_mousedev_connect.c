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
struct mousedev {int dummy; } ;
struct input_handler {int dummy; } ;
struct input_device_id {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mousedev*) ; 
 int PTR_ERR (struct mousedev*) ; 
 int mixdev_add_device (struct mousedev*) ; 
 struct mousedev* mousedev_create (struct input_dev*,struct input_handler*,int) ; 
 int /*<<< orphan*/  mousedev_destroy (struct mousedev*) ; 

__attribute__((used)) static int mousedev_connect(struct input_handler *handler,
			    struct input_dev *dev,
			    const struct input_device_id *id)
{
	struct mousedev *mousedev;
	int error;

	mousedev = mousedev_create(dev, handler, false);
	if (IS_ERR(mousedev))
		return PTR_ERR(mousedev);

	error = mixdev_add_device(mousedev);
	if (error) {
		mousedev_destroy(mousedev);
		return error;
	}

	return 0;
}