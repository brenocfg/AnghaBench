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
typedef  int u16 ;
struct videomode {scalar_t__ pixelclock; } ;
struct dispc_device {TYPE_1__* feat; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;
typedef  enum omap_dss_rotation_type { ____Placeholder_omap_dss_rotation_type } omap_dss_rotation_type ;
struct TYPE_2__ {int max_downscale; int (* calc_scaling ) (struct dispc_device*,unsigned long,unsigned long,struct videomode const*,int,int,int,int,int,int*,int*,int*,int*,int*,int,unsigned long*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_FRAC (int,int) ; 
 int DIV_ROUND_UP (int,int) ; 
#define  DRM_FORMAT_NV12 130 
#define  DRM_FORMAT_UYVY 129 
#define  DRM_FORMAT_YUYV 128 
 int /*<<< orphan*/  DSSDBG (char*,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FEAT_BURST_2D ; 
 int OMAP_DSS_OVL_CAP_SCALE ; 
 int OMAP_DSS_ROT_TILER ; 
 int OMAP_DSS_WB ; 
 unsigned long dispc_core_clk_rate (struct dispc_device*) ; 
 scalar_t__ dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dispc_device*,unsigned long,unsigned long,struct videomode const*,int,int,int,int,int,int*,int*,int*,int*,int*,int,unsigned long*,int) ; 

__attribute__((used)) static int dispc_ovl_calc_scaling(struct dispc_device *dispc,
				  enum omap_plane_id plane,
				  unsigned long pclk, unsigned long lclk,
				  enum omap_overlay_caps caps,
				  const struct videomode *vm,
				  u16 width, u16 height,
				  u16 out_width, u16 out_height,
				  u32 fourcc, bool *five_taps,
				  int *x_predecim, int *y_predecim, u16 pos_x,
				  enum omap_dss_rotation_type rotation_type,
				  bool mem_to_mem)
{
	int maxhdownscale = dispc->feat->max_downscale;
	int maxvdownscale = dispc->feat->max_downscale;
	const int max_decim_limit = 16;
	unsigned long core_clk = 0;
	int decim_x, decim_y, ret;

	if (width == out_width && height == out_height)
		return 0;

	if (plane == OMAP_DSS_WB) {
		switch (fourcc) {
		case DRM_FORMAT_NV12:
			maxhdownscale = maxvdownscale = 2;
			break;
		case DRM_FORMAT_YUYV:
		case DRM_FORMAT_UYVY:
			maxhdownscale = 2;
			maxvdownscale = 4;
			break;
		default:
			break;
		}
	}
	if (!mem_to_mem && (pclk == 0 || vm->pixelclock == 0)) {
		DSSERR("cannot calculate scaling settings: pclk is zero\n");
		return -EINVAL;
	}

	if ((caps & OMAP_DSS_OVL_CAP_SCALE) == 0)
		return -EINVAL;

	if (mem_to_mem) {
		*x_predecim = *y_predecim = 1;
	} else {
		*x_predecim = max_decim_limit;
		*y_predecim = (rotation_type == OMAP_DSS_ROT_TILER &&
				dispc_has_feature(dispc, FEAT_BURST_2D)) ?
				2 : max_decim_limit;
	}

	decim_x = DIV_ROUND_UP(DIV_ROUND_UP(width, out_width), maxhdownscale);
	decim_y = DIV_ROUND_UP(DIV_ROUND_UP(height, out_height), maxvdownscale);

	if (decim_x > *x_predecim || out_width > width * 8)
		return -EINVAL;

	if (decim_y > *y_predecim || out_height > height * 8)
		return -EINVAL;

	ret = dispc->feat->calc_scaling(dispc, pclk, lclk, vm, width, height,
					out_width, out_height, fourcc,
					five_taps, x_predecim, y_predecim,
					&decim_x, &decim_y, pos_x, &core_clk,
					mem_to_mem);
	if (ret)
		return ret;

	DSSDBG("%dx%d -> %dx%d (%d.%02d x %d.%02d), decim %dx%d %dx%d (%d.%02d x %d.%02d), taps %d, req clk %lu, cur clk %lu\n",
		width, height,
		out_width, out_height,
		out_width / width, DIV_FRAC(out_width, width),
		out_height / height, DIV_FRAC(out_height, height),

		decim_x, decim_y,
		width / decim_x, height / decim_y,
		out_width / (width / decim_x), DIV_FRAC(out_width, width / decim_x),
		out_height / (height / decim_y), DIV_FRAC(out_height, height / decim_y),

		*five_taps ? 5 : 3,
		core_clk, dispc_core_clk_rate(dispc));

	if (!core_clk || core_clk > dispc_core_clk_rate(dispc)) {
		DSSERR("failed to set up scaling, "
			"required core clk rate = %lu Hz, "
			"current core clk rate = %lu Hz\n",
			core_clk, dispc_core_clk_rate(dispc));
		return -EINVAL;
	}

	*x_predecim = decim_x;
	*y_predecim = decim_y;
	return 0;
}