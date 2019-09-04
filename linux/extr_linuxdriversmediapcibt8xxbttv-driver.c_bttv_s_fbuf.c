#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int width; int height; scalar_t__ bytesperline; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_framebuffer {int flags; TYPE_7__ fmt; int /*<<< orphan*/  base; } ;
struct file {int dummy; } ;
struct bttv_format {int flags; int depth; } ;
struct TYPE_12__ {int width; int height; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_18__ {scalar_t__ nclips; int /*<<< orphan*/ * clips; TYPE_3__ w; } ;
struct bttv_fh {struct bttv_format const* ovfmt; TYPE_9__ ov; int /*<<< orphan*/  do_crop; struct bttv* btv; } ;
struct bttv_buffer {int /*<<< orphan*/  crop; } ;
struct TYPE_13__ {int width; int height; } ;
struct TYPE_14__ {TYPE_4__ w; } ;
struct TYPE_15__ {TYPE_5__ ov; struct bttv_format const* ovfmt; } ;
struct TYPE_10__ {int width; int height; scalar_t__ bytesperline; } ;
struct TYPE_11__ {TYPE_1__ fmt; int /*<<< orphan*/  base; } ;
struct bttv {TYPE_8__* crop; TYPE_6__ init; TYPE_2__ fbuf; } ;
typedef  int __s32 ;
struct TYPE_17__ {int /*<<< orphan*/  rect; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EINVAL ; 
 int EPERM ; 
 int FORMAT_FLAGS_PACKED ; 
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int V4L2_FBUF_FLAG_OVERLAY ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  bttv_overlay_risc (struct bttv*,TYPE_9__*,struct bttv_format const*,struct bttv_buffer*) ; 
 int bttv_switch_overlay (struct bttv*,struct bttv_fh*,struct bttv_buffer*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ check_btres (struct bttv_fh*,int /*<<< orphan*/ ) ; 
 struct bttv_format* format_by_fourcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int limit_scaled_size_lock (struct bttv_fh*,int*,int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bttv_buffer* videobuf_sg_alloc (int) ; 

__attribute__((used)) static int bttv_s_fbuf(struct file *file, void *f,
				const struct v4l2_framebuffer *fb)
{
	struct bttv_fh *fh = f;
	struct bttv *btv = fh->btv;
	const struct bttv_format *fmt;
	int retval;

	if (!capable(CAP_SYS_ADMIN) &&
		!capable(CAP_SYS_RAWIO))
		return -EPERM;

	/* check args */
	fmt = format_by_fourcc(fb->fmt.pixelformat);
	if (NULL == fmt)
		return -EINVAL;
	if (0 == (fmt->flags & FORMAT_FLAGS_PACKED))
		return -EINVAL;

	retval = -EINVAL;
	if (fb->flags & V4L2_FBUF_FLAG_OVERLAY) {
		__s32 width = fb->fmt.width;
		__s32 height = fb->fmt.height;

		retval = limit_scaled_size_lock(fh, &width, &height,
					   V4L2_FIELD_INTERLACED,
					   /* width_mask */ ~3,
					   /* width_bias */ 2,
					   /* adjust_size */ 0,
					   /* adjust_crop */ 0);
		if (0 != retval)
			return retval;
	}

	/* ok, accept it */
	btv->fbuf.base       = fb->base;
	btv->fbuf.fmt.width  = fb->fmt.width;
	btv->fbuf.fmt.height = fb->fmt.height;
	if (0 != fb->fmt.bytesperline)
		btv->fbuf.fmt.bytesperline = fb->fmt.bytesperline;
	else
		btv->fbuf.fmt.bytesperline = btv->fbuf.fmt.width*fmt->depth/8;

	retval = 0;
	fh->ovfmt = fmt;
	btv->init.ovfmt = fmt;
	if (fb->flags & V4L2_FBUF_FLAG_OVERLAY) {
		fh->ov.w.left   = 0;
		fh->ov.w.top    = 0;
		fh->ov.w.width  = fb->fmt.width;
		fh->ov.w.height = fb->fmt.height;
		btv->init.ov.w.width  = fb->fmt.width;
		btv->init.ov.w.height = fb->fmt.height;

		kfree(fh->ov.clips);
		fh->ov.clips = NULL;
		fh->ov.nclips = 0;

		if (check_btres(fh, RESOURCE_OVERLAY)) {
			struct bttv_buffer *new;

			new = videobuf_sg_alloc(sizeof(*new));
			new->crop = btv->crop[!!fh->do_crop].rect;
			bttv_overlay_risc(btv, &fh->ov, fh->ovfmt, new);
			retval = bttv_switch_overlay(btv, fh, new);
		}
	}
	return retval;
}