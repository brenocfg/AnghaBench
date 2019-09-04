#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uvc_video_chain {TYPE_2__* dev; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  size; int /*<<< orphan*/  selector; } ;
struct uvc_control {int cached; TYPE_1__ info; TYPE_4__* entity; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  intfnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_CTRL_DATA_DEF ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_MAX ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_MIN ; 
 int /*<<< orphan*/  UVC_CTRL_DATA_RES ; 
 int UVC_CTRL_FLAG_GET_DEF ; 
 int UVC_CTRL_FLAG_GET_MAX ; 
 int UVC_CTRL_FLAG_GET_MIN ; 
 int UVC_CTRL_FLAG_GET_RES ; 
 scalar_t__ UVC_ENTITY_TYPE (TYPE_4__*) ; 
 int /*<<< orphan*/  UVC_GET_DEF ; 
 int /*<<< orphan*/  UVC_GET_MAX ; 
 int /*<<< orphan*/  UVC_GET_MIN ; 
 int /*<<< orphan*/  UVC_GET_RES ; 
 scalar_t__ UVC_VC_EXTENSION_UNIT ; 
 int /*<<< orphan*/  UVC_WARN_XU_GET_RES ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_ctrl_data (struct uvc_control*,int /*<<< orphan*/ ) ; 
 int uvc_query_ctrl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_warn_once (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int uvc_ctrl_populate_cache(struct uvc_video_chain *chain,
	struct uvc_control *ctrl)
{
	int ret;

	if (ctrl->info.flags & UVC_CTRL_FLAG_GET_DEF) {
		ret = uvc_query_ctrl(chain->dev, UVC_GET_DEF, ctrl->entity->id,
				     chain->dev->intfnum, ctrl->info.selector,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_DEF),
				     ctrl->info.size);
		if (ret < 0)
			return ret;
	}

	if (ctrl->info.flags & UVC_CTRL_FLAG_GET_MIN) {
		ret = uvc_query_ctrl(chain->dev, UVC_GET_MIN, ctrl->entity->id,
				     chain->dev->intfnum, ctrl->info.selector,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MIN),
				     ctrl->info.size);
		if (ret < 0)
			return ret;
	}
	if (ctrl->info.flags & UVC_CTRL_FLAG_GET_MAX) {
		ret = uvc_query_ctrl(chain->dev, UVC_GET_MAX, ctrl->entity->id,
				     chain->dev->intfnum, ctrl->info.selector,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_MAX),
				     ctrl->info.size);
		if (ret < 0)
			return ret;
	}
	if (ctrl->info.flags & UVC_CTRL_FLAG_GET_RES) {
		ret = uvc_query_ctrl(chain->dev, UVC_GET_RES, ctrl->entity->id,
				     chain->dev->intfnum, ctrl->info.selector,
				     uvc_ctrl_data(ctrl, UVC_CTRL_DATA_RES),
				     ctrl->info.size);
		if (ret < 0) {
			if (UVC_ENTITY_TYPE(ctrl->entity) !=
			    UVC_VC_EXTENSION_UNIT)
				return ret;

			/* GET_RES is mandatory for XU controls, but some
			 * cameras still choke on it. Ignore errors and set the
			 * resolution value to zero.
			 */
			uvc_warn_once(chain->dev, UVC_WARN_XU_GET_RES,
				      "UVC non compliance - GET_RES failed on "
				      "an XU control. Enabling workaround.\n");
			memset(uvc_ctrl_data(ctrl, UVC_CTRL_DATA_RES), 0,
			       ctrl->info.size);
		}
	}

	ctrl->cached = 1;
	return 0;
}