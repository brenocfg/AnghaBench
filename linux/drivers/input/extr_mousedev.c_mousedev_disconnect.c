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
struct input_handle {struct mousedev* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  mixdev_remove_device (struct mousedev*) ; 
 int /*<<< orphan*/  mousedev_destroy (struct mousedev*) ; 

__attribute__((used)) static void mousedev_disconnect(struct input_handle *handle)
{
	struct mousedev *mousedev = handle->private;

	mixdev_remove_device(mousedev);
	mousedev_destroy(mousedev);
}