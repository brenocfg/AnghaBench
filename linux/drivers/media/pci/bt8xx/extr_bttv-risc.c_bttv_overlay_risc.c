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
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct bttv_overlay {int field; size_t tvnorm; TYPE_2__ w; } ;
struct bttv_format {int /*<<< orphan*/  btswap; int /*<<< orphan*/  btformat; int /*<<< orphan*/  fourcc; } ;
struct TYPE_6__ {size_t field; } ;
struct bttv_buffer {TYPE_3__ vb; int /*<<< orphan*/  btswap; int /*<<< orphan*/  btformat; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  crop; int /*<<< orphan*/  geo; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr; } ;
struct bttv {TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  V4L2_FIELD_BOTTOM 130 
 int /*<<< orphan*/  V4L2_FIELD_HAS_BOTH (int) ; 
#define  V4L2_FIELD_INTERLACED 129 
#define  V4L2_FIELD_TOP 128 
 int /*<<< orphan*/  bttv_calc_geo (struct bttv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bttv_risc_overlay (struct bttv*,int /*<<< orphan*/ *,struct bttv_format const*,struct bttv_overlay*,int,int) ; 
 int /*<<< orphan*/ * bttv_tvnorms ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * v4l2_field_names ; 

int
bttv_overlay_risc(struct bttv *btv,
		  struct bttv_overlay *ov,
		  const struct bttv_format *fmt,
		  struct bttv_buffer *buf)
{
	/* check interleave, bottom+top fields */
	dprintk("%d: overlay fields: %s format: 0x%08x  size: %dx%d\n",
		btv->c.nr, v4l2_field_names[buf->vb.field],
		fmt->fourcc, ov->w.width, ov->w.height);

	/* calculate geometry */
	bttv_calc_geo(btv,&buf->geo,ov->w.width,ov->w.height,
		      V4L2_FIELD_HAS_BOTH(ov->field),
		      &bttv_tvnorms[ov->tvnorm],&buf->crop);

	/* build risc code */
	switch (ov->field) {
	case V4L2_FIELD_TOP:
		bttv_risc_overlay(btv, &buf->top,    fmt, ov, 0, 0);
		break;
	case V4L2_FIELD_BOTTOM:
		bttv_risc_overlay(btv, &buf->bottom, fmt, ov, 0, 0);
		break;
	case V4L2_FIELD_INTERLACED:
		bttv_risc_overlay(btv, &buf->top,    fmt, ov, 0, 1);
		bttv_risc_overlay(btv, &buf->bottom, fmt, ov, 1, 0);
		break;
	default:
		BUG();
	}

	/* copy format info */
	buf->btformat = fmt->btformat;
	buf->btswap   = fmt->btswap;
	buf->vb.field = ov->field;
	return 0;
}