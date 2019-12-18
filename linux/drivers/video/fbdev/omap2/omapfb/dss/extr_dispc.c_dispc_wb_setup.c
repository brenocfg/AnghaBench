#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct omap_video_timings {int x_res; int y_res; scalar_t__ vbp; scalar_t__ vsw; scalar_t__ vfp; } ;
struct omap_dss_writeback_info {int /*<<< orphan*/  color_mode; int /*<<< orphan*/  rotation_type; int /*<<< orphan*/  pre_mult_alpha; int /*<<< orphan*/  mirror; int /*<<< orphan*/  rotation; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  buf_width; int /*<<< orphan*/  p_uv_addr; int /*<<< orphan*/  paddr; } ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES2 (int) ; 
 int /*<<< orphan*/  DSSDBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
#define  OMAP_DSS_COLOR_ARGB16 135 
#define  OMAP_DSS_COLOR_ARGB16_1555 134 
#define  OMAP_DSS_COLOR_RGB12U 133 
#define  OMAP_DSS_COLOR_RGB16 132 
#define  OMAP_DSS_COLOR_RGB24P 131 
#define  OMAP_DSS_COLOR_RGBA16 130 
#define  OMAP_DSS_COLOR_RGBX16 129 
#define  OMAP_DSS_COLOR_XRGB16_1555 128 
 int OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA ; 
 int OMAP_DSS_OVL_CAP_SCALE ; 
 int OMAP_DSS_WB ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int dispc_ovl_setup_common (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int const,struct omap_video_timings const*,int) ; 
 int /*<<< orphan*/  dispc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (scalar_t__,int) ; 

int dispc_wb_setup(const struct omap_dss_writeback_info *wi,
		bool mem_to_mem, const struct omap_video_timings *mgr_timings)
{
	int r;
	u32 l;
	enum omap_plane plane = OMAP_DSS_WB;
	const int pos_x = 0, pos_y = 0;
	const u8 zorder = 0, global_alpha = 0;
	const bool replication = false;
	bool truncation;
	int in_width = mgr_timings->x_res;
	int in_height = mgr_timings->y_res;
	enum omap_overlay_caps caps =
		OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA;

	DSSDBG("dispc_wb_setup, pa %x, pa_uv %x, %d,%d -> %dx%d, cmode %x, "
		"rot %d, mir %d\n", wi->paddr, wi->p_uv_addr, in_width,
		in_height, wi->width, wi->height, wi->color_mode, wi->rotation,
		wi->mirror);

	r = dispc_ovl_setup_common(plane, caps, wi->paddr, wi->p_uv_addr,
		wi->buf_width, pos_x, pos_y, in_width, in_height, wi->width,
		wi->height, wi->color_mode, wi->rotation, wi->mirror, zorder,
		wi->pre_mult_alpha, global_alpha, wi->rotation_type,
		replication, mgr_timings, mem_to_mem);

	switch (wi->color_mode) {
	case OMAP_DSS_COLOR_RGB16:
	case OMAP_DSS_COLOR_RGB24P:
	case OMAP_DSS_COLOR_ARGB16:
	case OMAP_DSS_COLOR_RGBA16:
	case OMAP_DSS_COLOR_RGB12U:
	case OMAP_DSS_COLOR_ARGB16_1555:
	case OMAP_DSS_COLOR_XRGB16_1555:
	case OMAP_DSS_COLOR_RGBX16:
		truncation = true;
		break;
	default:
		truncation = false;
		break;
	}

	/* setup extra DISPC_WB_ATTRIBUTES */
	l = dispc_read_reg(DISPC_OVL_ATTRIBUTES(plane));
	l = FLD_MOD(l, truncation, 10, 10);	/* TRUNCATIONENABLE */
	l = FLD_MOD(l, mem_to_mem, 19, 19);	/* WRITEBACKMODE */
	if (mem_to_mem)
		l = FLD_MOD(l, 1, 26, 24);	/* CAPTUREMODE */
	else
		l = FLD_MOD(l, 0, 26, 24);	/* CAPTUREMODE */
	dispc_write_reg(DISPC_OVL_ATTRIBUTES(plane), l);

	if (mem_to_mem) {
		/* WBDELAYCOUNT */
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES2(plane), 0, 7, 0);
	} else {
		int wbdelay;

		wbdelay = min(mgr_timings->vfp + mgr_timings->vsw +
			mgr_timings->vbp, 255);

		/* WBDELAYCOUNT */
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES2(plane), wbdelay, 7, 0);
	}

	return r;
}