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
struct TYPE_5__ {int width; int height; } ;
struct TYPE_4__ {int /*<<< orphan*/ * base; } ;
struct viu_dev {TYPE_2__ crop_current; int /*<<< orphan*/ * ovfmt; TYPE_1__ ovbuf; } ;
struct TYPE_6__ {int width; int height; } ;
struct v4l2_window {int field; TYPE_3__ w; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_FIELD_ANY ; 
#define  V4L2_FIELD_BOTTOM 130 
#define  V4L2_FIELD_INTERLACED 129 
#define  V4L2_FIELD_TOP 128 

__attribute__((used)) static int verify_preview(struct viu_dev *dev, struct v4l2_window *win)
{
	enum v4l2_field field;
	int maxw, maxh;

	if (dev->ovbuf.base == NULL)
		return -EINVAL;
	if (dev->ovfmt == NULL)
		return -EINVAL;
	if (win->w.width < 48 || win->w.height < 32)
		return -EINVAL;

	field = win->field;
	maxw  = dev->crop_current.width;
	maxh  = dev->crop_current.height;

	if (field == V4L2_FIELD_ANY) {
		field = (win->w.height > maxh/2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_TOP;
	}
	switch (field) {
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
		maxh = maxh / 2;
		break;
	case V4L2_FIELD_INTERLACED:
		break;
	default:
		return -EINVAL;
	}

	win->field = field;
	if (win->w.width > maxw)
		win->w.width = maxw;
	if (win->w.height > maxh)
		win->w.height = maxh;
	return 0;
}