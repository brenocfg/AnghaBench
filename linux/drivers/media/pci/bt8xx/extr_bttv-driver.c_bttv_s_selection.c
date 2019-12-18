#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int left; int width; int top; int height; } ;
struct v4l2_selection {scalar_t__ type; scalar_t__ target; TYPE_2__ r; } ;
struct v4l2_rect {int left; int width; int top; int height; } ;
struct file {int dummy; } ;
struct bttv_fh {int do_crop; scalar_t__ width; scalar_t__ height; struct bttv* btv; } ;
struct bttv_crop {scalar_t__ min_scaled_width; scalar_t__ max_scaled_width; scalar_t__ min_scaled_height; scalar_t__ max_scaled_height; TYPE_2__ rect; } ;
struct TYPE_7__ {scalar_t__ width; scalar_t__ height; } ;
struct bttv {size_t tvnorm; TYPE_3__ init; struct bttv_crop* crop; int /*<<< orphan*/  vbi_end; } ;
typedef  int __s32 ;
struct TYPE_5__ {struct v4l2_rect bounds; } ;
struct TYPE_8__ {TYPE_1__ cropcap; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MAX_HDELAY ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OVERLAY ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 int /*<<< orphan*/  VIDEO_RESOURCES ; 
 int /*<<< orphan*/  bttv_crop_calc_limits (struct bttv_crop*) ; 
 TYPE_4__* bttv_tvnorms ; 
 void* clamp_t (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ locked_btres (struct bttv*,int /*<<< orphan*/ ) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  s32 ; 

__attribute__((used)) static int bttv_s_selection(struct file *file, void *f, struct v4l2_selection *sel)
{
	struct bttv_fh *fh = f;
	struct bttv *btv = fh->btv;
	const struct v4l2_rect *b;
	int retval;
	struct bttv_crop c;
	__s32 b_left;
	__s32 b_top;
	__s32 b_right;
	__s32 b_bottom;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    sel->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		return -EINVAL;

	if (sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	/* Make sure tvnorm, vbi_end and the current cropping
	   parameters remain consistent until we're done. Note
	   read() may change vbi_end in check_alloc_btres_lock(). */
	retval = -EBUSY;

	if (locked_btres(fh->btv, VIDEO_RESOURCES)) {
		return retval;
	}

	b = &bttv_tvnorms[btv->tvnorm].cropcap.bounds;

	b_left = b->left;
	b_right = b_left + b->width;
	b_bottom = b->top + b->height;

	b_top = max(b->top, btv->vbi_end);
	if (b_top + 32 >= b_bottom) {
		return retval;
	}

	/* Min. scaled size 48 x 32. */
	c.rect.left = clamp_t(s32, sel->r.left, b_left, b_right - 48);
	c.rect.left = min(c.rect.left, (__s32) MAX_HDELAY);

	c.rect.width = clamp_t(s32, sel->r.width,
			     48, b_right - c.rect.left);

	c.rect.top = clamp_t(s32, sel->r.top, b_top, b_bottom - 32);
	/* Top and height must be a multiple of two. */
	c.rect.top = (c.rect.top + 1) & ~1;

	c.rect.height = clamp_t(s32, sel->r.height,
			      32, b_bottom - c.rect.top);
	c.rect.height = (c.rect.height + 1) & ~1;

	bttv_crop_calc_limits(&c);

	sel->r = c.rect;

	btv->crop[1] = c;

	fh->do_crop = 1;

	if (fh->width < c.min_scaled_width) {
		fh->width = c.min_scaled_width;
		btv->init.width = c.min_scaled_width;
	} else if (fh->width > c.max_scaled_width) {
		fh->width = c.max_scaled_width;
		btv->init.width = c.max_scaled_width;
	}

	if (fh->height < c.min_scaled_height) {
		fh->height = c.min_scaled_height;
		btv->init.height = c.min_scaled_height;
	} else if (fh->height > c.max_scaled_height) {
		fh->height = c.max_scaled_height;
		btv->init.height = c.max_scaled_height;
	}

	return 0;
}