#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct uvc_device {int /*<<< orphan*/  intfnum; } ;
struct uvc_control_info {int flags; int /*<<< orphan*/  size; scalar_t__ selector; int /*<<< orphan*/  entity; scalar_t__ index; } ;
struct uvc_control {TYPE_2__* entity; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {int /*<<< orphan*/  guidExtensionCode; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; TYPE_1__ extension; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UVC_CTRL_FLAG_AUTO_UPDATE ; 
 int UVC_CTRL_FLAG_GET_CUR ; 
 int UVC_CTRL_FLAG_GET_DEF ; 
 int UVC_CTRL_FLAG_GET_MAX ; 
 int UVC_CTRL_FLAG_GET_MIN ; 
 int UVC_CTRL_FLAG_GET_RES ; 
 int UVC_CTRL_FLAG_SET_CUR ; 
 int /*<<< orphan*/  UVC_GET_LEN ; 
 int /*<<< orphan*/  UVC_TRACE_CONTROL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uvc_ctrl_fixup_xu_info (struct uvc_device*,struct uvc_control const*,struct uvc_control_info*) ; 
 int uvc_ctrl_get_flags (struct uvc_device*,struct uvc_control const*,struct uvc_control_info*) ; 
 int uvc_query_ctrl (struct uvc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int,...) ; 

__attribute__((used)) static int uvc_ctrl_fill_xu_info(struct uvc_device *dev,
	const struct uvc_control *ctrl, struct uvc_control_info *info)
{
	u8 *data;
	int ret;

	data = kmalloc(2, GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	memcpy(info->entity, ctrl->entity->extension.guidExtensionCode,
	       sizeof(info->entity));
	info->index = ctrl->index;
	info->selector = ctrl->index + 1;

	/* Query and verify the control length (GET_LEN) */
	ret = uvc_query_ctrl(dev, UVC_GET_LEN, ctrl->entity->id, dev->intfnum,
			     info->selector, data, 2);
	if (ret < 0) {
		uvc_trace(UVC_TRACE_CONTROL,
			  "GET_LEN failed on control %pUl/%u (%d).\n",
			   info->entity, info->selector, ret);
		goto done;
	}

	info->size = le16_to_cpup((__le16 *)data);

	info->flags = UVC_CTRL_FLAG_GET_MIN | UVC_CTRL_FLAG_GET_MAX
		    | UVC_CTRL_FLAG_GET_RES | UVC_CTRL_FLAG_GET_DEF;

	ret = uvc_ctrl_get_flags(dev, ctrl, info);
	if (ret < 0) {
		uvc_trace(UVC_TRACE_CONTROL,
			  "Failed to get flags for control %pUl/%u (%d).\n",
			  info->entity, info->selector, ret);
		goto done;
	}

	uvc_ctrl_fixup_xu_info(dev, ctrl, info);

	uvc_trace(UVC_TRACE_CONTROL, "XU control %pUl/%u queried: len %u, "
		  "flags { get %u set %u auto %u }.\n",
		  info->entity, info->selector, info->size,
		  (info->flags & UVC_CTRL_FLAG_GET_CUR) ? 1 : 0,
		  (info->flags & UVC_CTRL_FLAG_SET_CUR) ? 1 : 0,
		  (info->flags & UVC_CTRL_FLAG_AUTO_UPDATE) ? 1 : 0);

done:
	kfree(data);
	return ret;
}