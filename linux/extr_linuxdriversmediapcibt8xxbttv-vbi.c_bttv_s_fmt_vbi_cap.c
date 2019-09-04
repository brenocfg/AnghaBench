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
struct TYPE_8__ {int* start; } ;
struct TYPE_5__ {TYPE_4__ vbi; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct bttv_tvnorm {int* vbistart; } ;
struct TYPE_7__ {int /*<<< orphan*/  vb_lock; } ;
struct TYPE_6__ {int end; struct bttv_tvnorm const* tvnorm; TYPE_4__ fmt; } ;
struct bttv_fh {int resources; TYPE_3__ vbi; TYPE_2__ vbi_fmt; struct bttv* btv; } ;
struct bttv {size_t tvnorm; int /*<<< orphan*/  lock; int /*<<< orphan*/  crop_start; } ;
typedef  int __s32 ;

/* Variables and functions */
 int EBUSY ; 
 int RESOURCE_VBI ; 
 struct bttv_tvnorm* bttv_tvnorms ; 
 int max (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int try_fmt (TYPE_4__*,struct bttv_tvnorm const*,int /*<<< orphan*/ ) ; 

int bttv_s_fmt_vbi_cap(struct file *file, void *f, struct v4l2_format *frt)
{
	struct bttv_fh *fh = f;
	struct bttv *btv = fh->btv;
	const struct bttv_tvnorm *tvnorm;
	__s32 start1, end;
	int rc;

	mutex_lock(&btv->lock);

	rc = -EBUSY;
	if (fh->resources & RESOURCE_VBI)
		goto fail;

	tvnorm = &bttv_tvnorms[btv->tvnorm];

	rc = try_fmt(&frt->fmt.vbi, tvnorm, btv->crop_start);
	if (0 != rc)
		goto fail;

	start1 = frt->fmt.vbi.start[1] - tvnorm->vbistart[1] +
		tvnorm->vbistart[0];

	/* First possible line of video capturing. Should be
	   max(f->start[0] + f->count[0], start1 + f->count[1]) * 2
	   when capturing both fields. But for compatibility we must
	   pretend the VBI and video capture window may overlap,
	   so end = start + 1, the lowest possible value, times two
	   because vbi_fmt.end counts field lines times two. */
	end = max(frt->fmt.vbi.start[0], start1) * 2 + 2;

	mutex_lock(&fh->vbi.vb_lock);

	fh->vbi_fmt.fmt    = frt->fmt.vbi;
	fh->vbi_fmt.tvnorm = tvnorm;
	fh->vbi_fmt.end    = end;

	mutex_unlock(&fh->vbi.vb_lock);

	rc = 0;

 fail:
	mutex_unlock(&btv->lock);

	return rc;
}