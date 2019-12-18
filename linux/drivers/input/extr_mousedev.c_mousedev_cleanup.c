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
struct input_handle {int dummy; } ;
struct mousedev {scalar_t__ open; struct input_handle handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_close_device (struct input_handle*) ; 
 int /*<<< orphan*/  mousedev_hangup (struct mousedev*) ; 
 int /*<<< orphan*/  mousedev_mark_dead (struct mousedev*) ; 

__attribute__((used)) static void mousedev_cleanup(struct mousedev *mousedev)
{
	struct input_handle *handle = &mousedev->handle;

	mousedev_mark_dead(mousedev);
	mousedev_hangup(mousedev);

	/* mousedev is marked dead so no one else accesses mousedev->open */
	if (mousedev->open)
		input_close_device(handle);
}