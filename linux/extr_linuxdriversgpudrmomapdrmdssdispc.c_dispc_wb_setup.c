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
typedef  int u32 ;
struct videomode {int hactive; int vactive; int flags; int vsync_len; int vback_porch; int vfront_porch; } ;
struct omap_dss_writeback_info {int /*<<< orphan*/  fourcc; int /*<<< orphan*/  rotation_type; int /*<<< orphan*/  pre_mult_alpha; int /*<<< orphan*/  rotation; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  buf_width; int /*<<< orphan*/  p_uv_addr; int /*<<< orphan*/  paddr; } ;
struct dispc_device {int dummy; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;
typedef  enum dss_writeback_channel { ____Placeholder_dss_writeback_channel } dss_writeback_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES2 (int) ; 
 int DISPLAY_FLAGS_INTERLACED ; 
#define  DRM_FORMAT_ARGB1555 135 
#define  DRM_FORMAT_ARGB4444 134 
#define  DRM_FORMAT_RGB565 133 
#define  DRM_FORMAT_RGB888 132 
#define  DRM_FORMAT_RGBA4444 131 
#define  DRM_FORMAT_RGBX4444 130 
#define  DRM_FORMAT_XRGB1555 129 
#define  DRM_FORMAT_XRGB4444 128 
 int /*<<< orphan*/  DSSDBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DSS_WB_TV_MGR ; 
 int FLD_MOD (int,int,int,int) ; 
 int OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA ; 
 int OMAP_DSS_OVL_CAP_SCALE ; 
 int OMAP_DSS_WB ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dispc_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int dispc_ovl_setup_common (struct dispc_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int const,struct videomode const*,int) ; 
 int dispc_read_reg (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int) ; 
 int min (int,unsigned int) ; 

__attribute__((used)) static int dispc_wb_setup(struct dispc_device *dispc,
		   const struct omap_dss_writeback_info *wi,
		   bool mem_to_mem, const struct videomode *vm,
		   enum dss_writeback_channel channel_in)
{
	int r;
	u32 l;
	enum omap_plane_id plane = OMAP_DSS_WB;
	const int pos_x = 0, pos_y = 0;
	const u8 zorder = 0, global_alpha = 0;
	const bool replication = true;
	bool truncation;
	int in_width = vm->hactive;
	int in_height = vm->vactive;
	enum omap_overlay_caps caps =
		OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA;

	if (vm->flags & DISPLAY_FLAGS_INTERLACED)
		in_height /= 2;

	DSSDBG("dispc_wb_setup, pa %x, pa_uv %x, %d,%d -> %dx%d, cmode %x, "
		"rot %d\n", wi->paddr, wi->p_uv_addr, in_width,
		in_height, wi->width, wi->height, wi->fourcc, wi->rotation);

	r = dispc_ovl_setup_common(dispc, plane, caps, wi->paddr, wi->p_uv_addr,
		wi->buf_width, pos_x, pos_y, in_width, in_height, wi->width,
		wi->height, wi->fourcc, wi->rotation, zorder,
		wi->pre_mult_alpha, global_alpha, wi->rotation_type,
		replication, vm, mem_to_mem);
	if (r)
		return r;

	switch (wi->fourcc) {
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_RGB888:
	case DRM_FORMAT_ARGB4444:
	case DRM_FORMAT_RGBA4444:
	case DRM_FORMAT_RGBX4444:
	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_XRGB4444:
		truncation = true;
		break;
	default:
		truncation = false;
		break;
	}

	/* setup extra DISPC_WB_ATTRIBUTES */
	l = dispc_read_reg(dispc, DISPC_OVL_ATTRIBUTES(plane));
	l = FLD_MOD(l, truncation, 10, 10);	/* TRUNCATIONENABLE */
	l = FLD_MOD(l, channel_in, 18, 16);	/* CHANNELIN */
	l = FLD_MOD(l, mem_to_mem, 19, 19);	/* WRITEBACKMODE */
	if (mem_to_mem)
		l = FLD_MOD(l, 1, 26, 24);	/* CAPTUREMODE */
	else
		l = FLD_MOD(l, 0, 26, 24);	/* CAPTUREMODE */
	dispc_write_reg(dispc, DISPC_OVL_ATTRIBUTES(plane), l);

	if (mem_to_mem) {
		/* WBDELAYCOUNT */
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES2(plane), 0, 7, 0);
	} else {
		u32 wbdelay;

		if (channel_in == DSS_WB_TV_MGR)
			wbdelay = vm->vsync_len + vm->vback_porch;
		else
			wbdelay = vm->vfront_porch + vm->vsync_len +
				vm->vback_porch;

		if (vm->flags & DISPLAY_FLAGS_INTERLACED)
			wbdelay /= 2;

		wbdelay = min(wbdelay, 255u);

		/* WBDELAYCOUNT */
		REG_FLD_MOD(dispc, DISPC_OVL_ATTRIBUTES2(plane), wbdelay, 7, 0);
	}

	return 0;
}