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
struct drm_display_mode {int flags; int crtc_clock; scalar_t__ crtc_vblank_start; scalar_t__ crtc_vblank_end; scalar_t__ crtc_hblank_start; scalar_t__ crtc_hblank_end; scalar_t__ crtc_vdisplay; scalar_t__ crtc_vsync_end; scalar_t__ crtc_vsync_start; scalar_t__ crtc_hdisplay; scalar_t__ crtc_hsync_end; scalar_t__ crtc_hsync_start; scalar_t__ crtc_vtotal; scalar_t__ crtc_htotal; } ;
struct drm_crtc {TYPE_1__* state; } ;
struct arcpgu_drm_private {int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int ARCPGU_CTRL_HS_POL_MASK ; 
 int ARCPGU_CTRL_HS_POL_OFST ; 
 int ARCPGU_CTRL_VS_POL_MASK ; 
 int ARCPGU_CTRL_VS_POL_OFST ; 
 int /*<<< orphan*/  ARCPGU_REG_ACTIVE ; 
 int /*<<< orphan*/  ARCPGU_REG_CTRL ; 
 int /*<<< orphan*/  ARCPGU_REG_FMT ; 
 int /*<<< orphan*/  ARCPGU_REG_HSYNC ; 
 int /*<<< orphan*/  ARCPGU_REG_START_SET ; 
 int /*<<< orphan*/  ARCPGU_REG_STRIDE ; 
 int /*<<< orphan*/  ARCPGU_REG_VSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int ENCODE_PGU_XY (scalar_t__,scalar_t__) ; 
 int arc_pgu_read (struct arcpgu_drm_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_pgu_set_pxl_fmt (struct drm_crtc*) ; 
 int /*<<< orphan*/  arc_pgu_write (struct arcpgu_drm_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 struct arcpgu_drm_private* crtc_to_arcpgu_priv (struct drm_crtc*) ; 

__attribute__((used)) static void arc_pgu_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	struct arcpgu_drm_private *arcpgu = crtc_to_arcpgu_priv(crtc);
	struct drm_display_mode *m = &crtc->state->adjusted_mode;
	u32 val;

	arc_pgu_write(arcpgu, ARCPGU_REG_FMT,
		      ENCODE_PGU_XY(m->crtc_htotal, m->crtc_vtotal));

	arc_pgu_write(arcpgu, ARCPGU_REG_HSYNC,
		      ENCODE_PGU_XY(m->crtc_hsync_start - m->crtc_hdisplay,
				    m->crtc_hsync_end - m->crtc_hdisplay));

	arc_pgu_write(arcpgu, ARCPGU_REG_VSYNC,
		      ENCODE_PGU_XY(m->crtc_vsync_start - m->crtc_vdisplay,
				    m->crtc_vsync_end - m->crtc_vdisplay));

	arc_pgu_write(arcpgu, ARCPGU_REG_ACTIVE,
		      ENCODE_PGU_XY(m->crtc_hblank_end - m->crtc_hblank_start,
				    m->crtc_vblank_end - m->crtc_vblank_start));

	val = arc_pgu_read(arcpgu, ARCPGU_REG_CTRL);

	if (m->flags & DRM_MODE_FLAG_PVSYNC)
		val |= ARCPGU_CTRL_VS_POL_MASK << ARCPGU_CTRL_VS_POL_OFST;
	else
		val &= ~(ARCPGU_CTRL_VS_POL_MASK << ARCPGU_CTRL_VS_POL_OFST);

	if (m->flags & DRM_MODE_FLAG_PHSYNC)
		val |= ARCPGU_CTRL_HS_POL_MASK << ARCPGU_CTRL_HS_POL_OFST;
	else
		val &= ~(ARCPGU_CTRL_HS_POL_MASK << ARCPGU_CTRL_HS_POL_OFST);

	arc_pgu_write(arcpgu, ARCPGU_REG_CTRL, val);
	arc_pgu_write(arcpgu, ARCPGU_REG_STRIDE, 0);
	arc_pgu_write(arcpgu, ARCPGU_REG_START_SET, 1);

	arc_pgu_set_pxl_fmt(crtc);

	clk_set_rate(arcpgu->clk, m->crtc_clock * 1000);
}