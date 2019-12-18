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
struct v4l2_subdev {TYPE_1__* internal_ops; struct module* owner; int /*<<< orphan*/  owner_v4l2_dev; } ;
struct module {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct v4l2_subdev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_subdev*) ; 

__attribute__((used)) static void v4l2_subdev_release(struct v4l2_subdev *sd)
{
	struct module *owner = !sd->owner_v4l2_dev ? sd->owner : NULL;

	if (sd->internal_ops && sd->internal_ops->release)
		sd->internal_ops->release(sd);
	module_put(owner);
}