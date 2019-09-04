#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int grp_id; int /*<<< orphan*/  name; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int dummy; } ;
struct TYPE_6__ {struct v4l2_subdev** sd; TYPE_2__* config; } ;
struct TYPE_5__ {int subdev_count; TYPE_1__* subdevinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ vpif_obj ; 

__attribute__((used)) static int vpif_async_bound(struct v4l2_async_notifier *notifier,
			    struct v4l2_subdev *subdev,
			    struct v4l2_async_subdev *asd)
{
	int i;

	for (i = 0; i < vpif_obj.config->subdev_count; i++)
		if (!strcmp(vpif_obj.config->subdevinfo[i].name,
			    subdev->name)) {
			vpif_obj.sd[i] = subdev;
			vpif_obj.sd[i]->grp_id = 1 << i;
			return 0;
		}

	return -EINVAL;
}