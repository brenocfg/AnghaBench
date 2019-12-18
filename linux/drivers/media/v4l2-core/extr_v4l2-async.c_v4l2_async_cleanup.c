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
struct v4l2_subdev {int /*<<< orphan*/ * asd; int /*<<< orphan*/  async_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static void v4l2_async_cleanup(struct v4l2_subdev *sd)
{
	v4l2_device_unregister_subdev(sd);
	/*
	 * Subdevice driver will reprobe and put the subdev back
	 * onto the list
	 */
	list_del_init(&sd->async_list);
	sd->asd = NULL;
}