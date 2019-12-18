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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_bt_timings {int hbackporch; int hsync; int width; int height; int vbackporch; int vsync; int il_vbackporch; int il_vsync; int il_vfrontporch; int vfrontporch; scalar_t__ interlaced; } ;
struct TYPE_2__ {struct v4l2_bt_timings bt; } ;
struct tda1997x_state {scalar_t__ chip_revision; TYPE_1__ timings; } ;

/* Variables and functions */
 int MASK_VHREF ; 
 int /*<<< orphan*/  REG_FDW_E ; 
 int /*<<< orphan*/  REG_FDW_S ; 
 int /*<<< orphan*/  REG_FREF_F1_S ; 
 int /*<<< orphan*/  REG_FREF_F2_S ; 
 int /*<<< orphan*/  REG_HREF_E ; 
 int /*<<< orphan*/  REG_HREF_S ; 
 int /*<<< orphan*/  REG_LCNT_NLIN ; 
 int /*<<< orphan*/  REG_LCNT_PR ; 
 int /*<<< orphan*/  REG_PXCNT_NPIX ; 
 int /*<<< orphan*/  REG_PXCNT_PR ; 
 int /*<<< orphan*/  REG_VHREF_CTRL ; 
 int /*<<< orphan*/  REG_VREF_F1_S ; 
 int /*<<< orphan*/  REG_VREF_F1_WIDTH ; 
 int /*<<< orphan*/  REG_VREF_F2_S ; 
 int /*<<< orphan*/  REG_VREF_F2_WIDTH ; 
 int V4L2_DV_BT_FRAME_HEIGHT (struct v4l2_bt_timings const*) ; 
 int V4L2_DV_BT_FRAME_WIDTH (struct v4l2_bt_timings const*) ; 
 int VHREF_STD_DET_OFF ; 
 int VHREF_STD_DET_SHIFT ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  io_write16 (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct tda1997x_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void
tda1997x_configure_vhref(struct v4l2_subdev *sd)
{
	struct tda1997x_state *state = to_state(sd);
	const struct v4l2_bt_timings *bt = &state->timings.bt;
	int width, lines;
	u16 href_start, href_end;
	u16 vref_f1_start, vref_f2_start;
	u8 vref_f1_width, vref_f2_width;
	u8 field_polarity;
	u16 fieldref_f1_start, fieldref_f2_start;
	u8 reg;

	href_start = bt->hbackporch + bt->hsync + 1;
	href_end = href_start + bt->width;
	vref_f1_start = bt->height + bt->vbackporch + bt->vsync +
			bt->il_vbackporch + bt->il_vsync +
			bt->il_vfrontporch;
	vref_f1_width = bt->vbackporch + bt->vsync + bt->vfrontporch;
	vref_f2_start = 0;
	vref_f2_width = 0;
	fieldref_f1_start = 0;
	fieldref_f2_start = 0;
	if (bt->interlaced) {
		vref_f2_start = (bt->height / 2) +
				(bt->il_vbackporch + bt->il_vsync - 1);
		vref_f2_width = bt->il_vbackporch + bt->il_vsync +
				bt->il_vfrontporch;
		fieldref_f2_start = vref_f2_start + bt->il_vfrontporch +
				    fieldref_f1_start;
	}
	field_polarity = 0;

	width = V4L2_DV_BT_FRAME_WIDTH(bt);
	lines = V4L2_DV_BT_FRAME_HEIGHT(bt);

	/*
	 * Configure Frame Detection Window:
	 *  horiz area where the VHREF module consider a VSYNC a new frame
	 */
	io_write16(sd, REG_FDW_S, 0x2ef); /* start position */
	io_write16(sd, REG_FDW_E, 0x141); /* end position */

	/* Set Pixel And Line Counters */
	if (state->chip_revision == 0)
		io_write16(sd, REG_PXCNT_PR, 4);
	else
		io_write16(sd, REG_PXCNT_PR, 1);
	io_write16(sd, REG_PXCNT_NPIX, width & MASK_VHREF);
	io_write16(sd, REG_LCNT_PR, 1);
	io_write16(sd, REG_LCNT_NLIN, lines & MASK_VHREF);

	/*
	 * Configure the VHRef timing generator responsible for rebuilding all
	 * horiz and vert synch and ref signals from its input allowing auto
	 * detection algorithms and forcing predefined modes (480i & 576i)
	 */
	reg = VHREF_STD_DET_OFF << VHREF_STD_DET_SHIFT;
	io_write(sd, REG_VHREF_CTRL, reg);

	/*
	 * Configure the VHRef timing values. In case the VHREF generator has
	 * been configured in manual mode, this will allow to manually set all
	 * horiz and vert ref values (non-active pixel areas) of the generator
	 * and allows setting the frame reference params.
	 */
	/* horizontal reference start/end */
	io_write16(sd, REG_HREF_S, href_start & MASK_VHREF);
	io_write16(sd, REG_HREF_E, href_end & MASK_VHREF);
	/* vertical reference f1 start/end */
	io_write16(sd, REG_VREF_F1_S, vref_f1_start & MASK_VHREF);
	io_write(sd, REG_VREF_F1_WIDTH, vref_f1_width);
	/* vertical reference f2 start/end */
	io_write16(sd, REG_VREF_F2_S, vref_f2_start & MASK_VHREF);
	io_write(sd, REG_VREF_F2_WIDTH, vref_f2_width);

	/* F1/F2 FREF, field polarity */
	reg = fieldref_f1_start & MASK_VHREF;
	reg |= field_polarity << 8;
	io_write16(sd, REG_FREF_F1_S, reg);
	reg = fieldref_f2_start & MASK_VHREF;
	io_write16(sd, REG_FREF_F2_S, reg);
}