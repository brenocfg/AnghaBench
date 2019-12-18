#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_frmsizeenum {scalar_t__ index; int pixel_format; TYPE_1__ discrete; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
#define  V4L2_PIX_FMT_RGB565 132 
#define  V4L2_PIX_FMT_RGB565X 131 
#define  V4L2_PIX_FMT_SBGGR8 130 
#define  V4L2_PIX_FMT_UYVY 129 
#define  V4L2_PIX_FMT_YUYV 128 
 TYPE_2__* stk_sizes ; 

__attribute__((used)) static int stk_vidioc_enum_framesizes(struct file *filp,
		void *priv, struct v4l2_frmsizeenum *frms)
{
	if (frms->index >= ARRAY_SIZE(stk_sizes))
		return -EINVAL;
	switch (frms->pixel_format) {
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_RGB565X:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_SBGGR8:
		frms->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		frms->discrete.width = stk_sizes[frms->index].w;
		frms->discrete.height = stk_sizes[frms->index].h;
		return 0;
	default: return -EINVAL;
	}
}