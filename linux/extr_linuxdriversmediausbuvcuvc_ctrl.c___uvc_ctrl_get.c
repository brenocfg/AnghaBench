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
struct uvc_video_chain {TYPE_3__* dev; } ;
struct uvc_control_mapping {int dummy; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  size; int /*<<< orphan*/  selector; } ;
struct uvc_control {int loaded; TYPE_2__ info; TYPE_1__* entity; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_6__ {int /*<<< orphan*/  intfnum; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_CURRENT ; 
 int UVC_CTRL_FLAG_GET_CUR ; 
 int /*<<< orphan*/  UVC_GET_CUR ; 
 int /*<<< orphan*/  __uvc_ctrl_get_value (struct uvc_control_mapping*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_ctrl_data (struct uvc_control*,int /*<<< orphan*/ ) ; 
 int uvc_query_ctrl (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __uvc_ctrl_get(struct uvc_video_chain *chain,
	struct uvc_control *ctrl, struct uvc_control_mapping *mapping,
	s32 *value)
{
	int ret;

	if ((ctrl->info.flags & UVC_CTRL_FLAG_GET_CUR) == 0)
		return -EACCES;

	if (!ctrl->loaded) {
		ret = uvc_query_ctrl(chain->dev, UVC_GET_CUR, ctrl->entity->id,
				chain->dev->intfnum, ctrl->info.selector,
				uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT),
				ctrl->info.size);
		if (ret < 0)
			return ret;

		ctrl->loaded = 1;
	}

	*value = __uvc_ctrl_get_value(mapping,
				uvc_ctrl_data(ctrl, UVC_CTRL_DATA_CURRENT));

	return 0;
}