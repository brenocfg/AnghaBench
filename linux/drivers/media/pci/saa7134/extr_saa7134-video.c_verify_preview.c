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
struct TYPE_6__ {int width; int height; } ;
struct v4l2_window {int clipcount; int field; TYPE_3__ w; scalar_t__ global_alpha; scalar_t__ chromakey; } ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_4__ {int /*<<< orphan*/ * base; } ;
struct saa7134_dev {TYPE_2__ crop_current; int /*<<< orphan*/ * ovfmt; TYPE_1__ ovbuf; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_FIELD_ANY ; 
#define  V4L2_FIELD_BOTTOM 129 
 int V4L2_FIELD_INTERLACED ; 
#define  V4L2_FIELD_TOP 128 

__attribute__((used)) static int verify_preview(struct saa7134_dev *dev, struct v4l2_window *win, bool try)
{
	enum v4l2_field field;
	int maxw, maxh;

	if (!try && (dev->ovbuf.base == NULL || dev->ovfmt == NULL))
		return -EINVAL;
	if (win->w.width < 48)
		win->w.width = 48;
	if (win->w.height < 32)
		win->w.height = 32;
	if (win->clipcount > 8)
		win->clipcount = 8;

	win->chromakey = 0;
	win->global_alpha = 0;
	field = win->field;
	maxw  = dev->crop_current.width;
	maxh  = dev->crop_current.height;

	if (V4L2_FIELD_ANY == field) {
		field = (win->w.height > maxh/2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_TOP;
	}
	switch (field) {
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
		maxh = maxh / 2;
		break;
	default:
		field = V4L2_FIELD_INTERLACED;
		break;
	}

	win->field = field;
	if (win->w.width > maxw)
		win->w.width = maxw;
	if (win->w.height > maxh)
		win->w.height = maxh;
	return 0;
}