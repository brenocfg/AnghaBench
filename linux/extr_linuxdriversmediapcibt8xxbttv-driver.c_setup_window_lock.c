#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_window {int clipcount; int /*<<< orphan*/  field; TYPE_9__ w; int /*<<< orphan*/  clips; } ;
struct v4l2_clip {int dummy; } ;
struct TYPE_17__ {int nclips; int setup_ok; int /*<<< orphan*/  field; TYPE_9__ w; struct v4l2_clip* clips; } ;
struct bttv_fh {TYPE_8__* ovfmt; TYPE_7__ ov; int /*<<< orphan*/  do_crop; } ;
struct bttv_buffer {int /*<<< orphan*/  crop; } ;
struct TYPE_13__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {int /*<<< orphan*/  field; TYPE_3__ w; } ;
struct TYPE_15__ {TYPE_4__ ov; } ;
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_12__ {TYPE_1__ fmt; int /*<<< orphan*/ * base; } ;
struct bttv {TYPE_6__* crop; TYPE_5__ init; TYPE_2__ fbuf; } ;
struct TYPE_18__ {int flags; int depth; } ;
struct TYPE_16__ {int /*<<< orphan*/  rect; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FORMAT_FLAGS_PACKED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int /*<<< orphan*/  btcx_align (TYPE_9__*,struct v4l2_clip*,int,int) ; 
 int btcx_screen_clips (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*,struct v4l2_clip*,int) ; 
 int /*<<< orphan*/  btcx_sort_clips (struct v4l2_clip*,int) ; 
 int /*<<< orphan*/  bttv_overlay_risc (struct bttv*,TYPE_7__*,TYPE_8__*,struct bttv_buffer*) ; 
 int bttv_switch_overlay (struct bttv*,struct bttv_fh*,struct bttv_buffer*) ; 
 scalar_t__ check_btres (struct bttv_fh*,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (struct v4l2_clip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct v4l2_clip*) ; 
 struct v4l2_clip* kmalloc (int,int /*<<< orphan*/ ) ; 
 int verify_window_lock (struct bttv_fh*,struct v4l2_window*,int,int) ; 
 struct bttv_buffer* videobuf_sg_alloc (int) ; 

__attribute__((used)) static int setup_window_lock(struct bttv_fh *fh, struct bttv *btv,
			struct v4l2_window *win, int fixup)
{
	struct v4l2_clip *clips = NULL;
	int n,size,retval = 0;

	if (NULL == fh->ovfmt)
		return -EINVAL;
	if (!(fh->ovfmt->flags & FORMAT_FLAGS_PACKED))
		return -EINVAL;
	retval = verify_window_lock(fh, win,
			       /* adjust_size */ fixup,
			       /* adjust_crop */ fixup);
	if (0 != retval)
		return retval;

	/* copy clips  --  luckily v4l1 + v4l2 are binary
	   compatible here ...*/
	n = win->clipcount;
	size = sizeof(*clips)*(n+4);
	clips = kmalloc(size,GFP_KERNEL);
	if (NULL == clips)
		return -ENOMEM;
	if (n > 0) {
		if (copy_from_user(clips,win->clips,sizeof(struct v4l2_clip)*n)) {
			kfree(clips);
			return -EFAULT;
		}
	}

	/* clip against screen */
	if (NULL != btv->fbuf.base)
		n = btcx_screen_clips(btv->fbuf.fmt.width, btv->fbuf.fmt.height,
				      &win->w, clips, n);
	btcx_sort_clips(clips,n);

	/* 4-byte alignments */
	switch (fh->ovfmt->depth) {
	case 8:
	case 24:
		btcx_align(&win->w, clips, n, 3);
		break;
	case 16:
		btcx_align(&win->w, clips, n, 1);
		break;
	case 32:
		/* no alignment fixups needed */
		break;
	default:
		BUG();
	}

	kfree(fh->ov.clips);
	fh->ov.clips    = clips;
	fh->ov.nclips   = n;

	fh->ov.w        = win->w;
	fh->ov.field    = win->field;
	fh->ov.setup_ok = 1;

	btv->init.ov.w.width   = win->w.width;
	btv->init.ov.w.height  = win->w.height;
	btv->init.ov.field     = win->field;

	/* update overlay if needed */
	retval = 0;
	if (check_btres(fh, RESOURCE_OVERLAY)) {
		struct bttv_buffer *new;

		new = videobuf_sg_alloc(sizeof(*new));
		new->crop = btv->crop[!!fh->do_crop].rect;
		bttv_overlay_risc(btv, &fh->ov, fh->ovfmt, new);
		retval = bttv_switch_overlay(btv,fh,new);
	}
	return retval;
}