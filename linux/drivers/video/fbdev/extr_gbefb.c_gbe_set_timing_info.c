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
typedef  int u32 ;
struct gbe_timing_info {int pll_m; int pll_n; int pll_p; int htotal; int vtotal; int vsync_start; int vsync_end; int hsync_start; int hsync_end; int vblank_start; int vblank_end; int hblank_start; int hblank_end; int width; } ;
struct TYPE_2__ {unsigned int dotclock; unsigned int vt_xymax; unsigned int vt_vsync; unsigned int vt_hsync; unsigned int vt_vblank; unsigned int vt_hblank; unsigned int vt_vcmap; unsigned int vt_hcmap; unsigned int did_start_xy; unsigned int crs_start_xy; unsigned int vc_start_xy; unsigned int vt_hpixen; unsigned int vt_vpixen; unsigned int vt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRS_STARTX ; 
 int /*<<< orphan*/  CRS_STARTY ; 
 int /*<<< orphan*/  CRS_START_XY ; 
 int /*<<< orphan*/  DID_STARTX ; 
 int /*<<< orphan*/  DID_STARTY ; 
 int /*<<< orphan*/  DID_START_XY ; 
 int /*<<< orphan*/  DOTCLK ; 
 int GBE_CRS_MAGIC ; 
 int GBE_PIXEN_MAGIC_OFF ; 
 int GBE_PIXEN_MAGIC_ON ; 
 int /*<<< orphan*/  HBLANK_OFF ; 
 int /*<<< orphan*/  HBLANK_ON ; 
 int /*<<< orphan*/  HCMAP_OFF ; 
 int /*<<< orphan*/  HCMAP_ON ; 
 int /*<<< orphan*/  HPIXEN_OFF ; 
 int /*<<< orphan*/  HPIXEN_ON ; 
 int /*<<< orphan*/  HSYNC_OFF ; 
 int /*<<< orphan*/  HSYNC_ON ; 
 int /*<<< orphan*/  M ; 
 int /*<<< orphan*/  MAXX ; 
 int /*<<< orphan*/  MAXY ; 
 int /*<<< orphan*/  N ; 
 int /*<<< orphan*/  P ; 
 int /*<<< orphan*/  RUN ; 
 int /*<<< orphan*/  SET_GBE_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  SYNC_LOW ; 
 int /*<<< orphan*/  VBLANK_OFF ; 
 int /*<<< orphan*/  VBLANK_ON ; 
 int /*<<< orphan*/  VCMAP_OFF ; 
 int /*<<< orphan*/  VCMAP_ON ; 
 int /*<<< orphan*/  VC_STARTX ; 
 int /*<<< orphan*/  VC_STARTY ; 
 int /*<<< orphan*/  VC_START_XY ; 
 int /*<<< orphan*/  VPIXEN_OFF ; 
 int /*<<< orphan*/  VPIXEN_ON ; 
 int /*<<< orphan*/  VSYNC_OFF ; 
 int /*<<< orphan*/  VSYNC_ON ; 
 int /*<<< orphan*/  VT_FLAGS ; 
 int /*<<< orphan*/  VT_HBLANK ; 
 int /*<<< orphan*/  VT_HCMAP ; 
 int /*<<< orphan*/  VT_HPIXEN ; 
 int /*<<< orphan*/  VT_HSYNC ; 
 int /*<<< orphan*/  VT_VBLANK ; 
 int /*<<< orphan*/  VT_VCMAP ; 
 int /*<<< orphan*/  VT_VPIXEN ; 
 int /*<<< orphan*/  VT_VSYNC ; 
 int /*<<< orphan*/  VT_XYMAX ; 
 scalar_t__ flat_panel_enabled ; 
 TYPE_1__* gbe ; 
 int /*<<< orphan*/  gbefb_setup_flatpanel (struct gbe_timing_info*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void gbe_set_timing_info(struct gbe_timing_info *timing)
{
	int temp;
	unsigned int val;

	/* setup dot clock PLL */
	val = 0;
	SET_GBE_FIELD(DOTCLK, M, val, timing->pll_m - 1);
	SET_GBE_FIELD(DOTCLK, N, val, timing->pll_n - 1);
	SET_GBE_FIELD(DOTCLK, P, val, timing->pll_p);
	SET_GBE_FIELD(DOTCLK, RUN, val, 0);	/* do not start yet */
	gbe->dotclock = val;
	mdelay(10);

	/* setup pixel counter */
	val = 0;
	SET_GBE_FIELD(VT_XYMAX, MAXX, val, timing->htotal);
	SET_GBE_FIELD(VT_XYMAX, MAXY, val, timing->vtotal);
	gbe->vt_xymax = val;

	/* setup video timing signals */
	val = 0;
	SET_GBE_FIELD(VT_VSYNC, VSYNC_ON, val, timing->vsync_start);
	SET_GBE_FIELD(VT_VSYNC, VSYNC_OFF, val, timing->vsync_end);
	gbe->vt_vsync = val;
	val = 0;
	SET_GBE_FIELD(VT_HSYNC, HSYNC_ON, val, timing->hsync_start);
	SET_GBE_FIELD(VT_HSYNC, HSYNC_OFF, val, timing->hsync_end);
	gbe->vt_hsync = val;
	val = 0;
	SET_GBE_FIELD(VT_VBLANK, VBLANK_ON, val, timing->vblank_start);
	SET_GBE_FIELD(VT_VBLANK, VBLANK_OFF, val, timing->vblank_end);
	gbe->vt_vblank = val;
	val = 0;
	SET_GBE_FIELD(VT_HBLANK, HBLANK_ON, val,
		      timing->hblank_start - 5);
	SET_GBE_FIELD(VT_HBLANK, HBLANK_OFF, val,
		      timing->hblank_end - 3);
	gbe->vt_hblank = val;

	/* setup internal timing signals */
	val = 0;
	SET_GBE_FIELD(VT_VCMAP, VCMAP_ON, val, timing->vblank_start);
	SET_GBE_FIELD(VT_VCMAP, VCMAP_OFF, val, timing->vblank_end);
	gbe->vt_vcmap = val;
	val = 0;
	SET_GBE_FIELD(VT_HCMAP, HCMAP_ON, val, timing->hblank_start);
	SET_GBE_FIELD(VT_HCMAP, HCMAP_OFF, val, timing->hblank_end);
	gbe->vt_hcmap = val;

	val = 0;
	temp = timing->vblank_start - timing->vblank_end - 1;
	if (temp > 0)
		temp = -temp;

	if (flat_panel_enabled)
		gbefb_setup_flatpanel(timing);

	SET_GBE_FIELD(DID_START_XY, DID_STARTY, val, (u32) temp);
	if (timing->hblank_end >= 20)
		SET_GBE_FIELD(DID_START_XY, DID_STARTX, val,
			      timing->hblank_end - 20);
	else
		SET_GBE_FIELD(DID_START_XY, DID_STARTX, val,
			      timing->htotal - (20 - timing->hblank_end));
	gbe->did_start_xy = val;

	val = 0;
	SET_GBE_FIELD(CRS_START_XY, CRS_STARTY, val, (u32) (temp + 1));
	if (timing->hblank_end >= GBE_CRS_MAGIC)
		SET_GBE_FIELD(CRS_START_XY, CRS_STARTX, val,
			      timing->hblank_end - GBE_CRS_MAGIC);
	else
		SET_GBE_FIELD(CRS_START_XY, CRS_STARTX, val,
			      timing->htotal - (GBE_CRS_MAGIC -
						timing->hblank_end));
	gbe->crs_start_xy = val;

	val = 0;
	SET_GBE_FIELD(VC_START_XY, VC_STARTY, val, (u32) temp);
	SET_GBE_FIELD(VC_START_XY, VC_STARTX, val, timing->hblank_end - 4);
	gbe->vc_start_xy = val;

	val = 0;
	temp = timing->hblank_end - GBE_PIXEN_MAGIC_ON;
	if (temp < 0)
		temp += timing->htotal;	/* allow blank to wrap around */

	SET_GBE_FIELD(VT_HPIXEN, HPIXEN_ON, val, temp);
	SET_GBE_FIELD(VT_HPIXEN, HPIXEN_OFF, val,
		      ((temp + timing->width -
			GBE_PIXEN_MAGIC_OFF) % timing->htotal));
	gbe->vt_hpixen = val;

	val = 0;
	SET_GBE_FIELD(VT_VPIXEN, VPIXEN_ON, val, timing->vblank_end);
	SET_GBE_FIELD(VT_VPIXEN, VPIXEN_OFF, val, timing->vblank_start);
	gbe->vt_vpixen = val;

	/* turn off sync on green */
	val = 0;
	SET_GBE_FIELD(VT_FLAGS, SYNC_LOW, val, 1);
	gbe->vt_flags = val;
}