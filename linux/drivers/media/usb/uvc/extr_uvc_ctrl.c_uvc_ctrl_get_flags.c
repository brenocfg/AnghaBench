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
typedef  int u8 ;
struct uvc_device {int /*<<< orphan*/  intfnum; } ;
struct uvc_control_info {int flags; int /*<<< orphan*/  selector; } ;
struct uvc_control {TYPE_1__* entity; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UVC_CONTROL_CAP_ASYNCHRONOUS ; 
 int UVC_CONTROL_CAP_AUTOUPDATE ; 
 int UVC_CONTROL_CAP_GET ; 
 int UVC_CONTROL_CAP_SET ; 
 int UVC_CTRL_FLAG_ASYNCHRONOUS ; 
 int UVC_CTRL_FLAG_AUTO_UPDATE ; 
 int UVC_CTRL_FLAG_GET_CUR ; 
 int UVC_CTRL_FLAG_SET_CUR ; 
 int /*<<< orphan*/  UVC_GET_INFO ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int uvc_query_ctrl (struct uvc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int uvc_ctrl_get_flags(struct uvc_device *dev,
			      const struct uvc_control *ctrl,
			      struct uvc_control_info *info)
{
	u8 *data;
	int ret;

	data = kmalloc(1, GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	ret = uvc_query_ctrl(dev, UVC_GET_INFO, ctrl->entity->id, dev->intfnum,
			     info->selector, data, 1);
	if (!ret)
		info->flags |= (data[0] & UVC_CONTROL_CAP_GET ?
				UVC_CTRL_FLAG_GET_CUR : 0)
			    |  (data[0] & UVC_CONTROL_CAP_SET ?
				UVC_CTRL_FLAG_SET_CUR : 0)
			    |  (data[0] & UVC_CONTROL_CAP_AUTOUPDATE ?
				UVC_CTRL_FLAG_AUTO_UPDATE : 0)
			    |  (data[0] & UVC_CONTROL_CAP_ASYNCHRONOUS ?
				UVC_CTRL_FLAG_ASYNCHRONOUS : 0);

	kfree(data);
	return ret;
}