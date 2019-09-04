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
struct v4l2_selection {scalar_t__ type; int target; int /*<<< orphan*/  r; } ;
struct file {int dummy; } ;
struct bttv_fh {int /*<<< orphan*/  do_crop; struct bttv* btv; } ;
struct bttv {size_t tvnorm; TYPE_1__* crop; } ;
struct TYPE_5__ {int /*<<< orphan*/  bounds; int /*<<< orphan*/  defrect; } ;
struct TYPE_6__ {TYPE_2__ cropcap; } ;
struct TYPE_4__ {int /*<<< orphan*/  rect; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OVERLAY ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 TYPE_3__* bttv_tvnorms ; 

__attribute__((used)) static int bttv_g_selection(struct file *file, void *f, struct v4l2_selection *sel)
{
	struct bttv_fh *fh = f;
	struct bttv *btv = fh->btv;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    sel->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
		/*
		 * No fh->do_crop = 1; because btv->crop[1] may be
		 * inconsistent with fh->width or fh->height and apps
		 * do not expect a change here.
		 */
		sel->r = btv->crop[!!fh->do_crop].rect;
		break;
	case V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r = bttv_tvnorms[btv->tvnorm].cropcap.defrect;
		break;
	case V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r = bttv_tvnorms[btv->tvnorm].cropcap.bounds;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}