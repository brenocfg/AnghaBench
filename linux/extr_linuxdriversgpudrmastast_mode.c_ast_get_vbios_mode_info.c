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
typedef  int u8 ;
typedef  size_t u32 ;
struct drm_framebuffer {TYPE_3__* format; } ;
struct drm_display_mode {int flags; int clock; int crtc_hdisplay; int crtc_vdisplay; scalar_t__ crtc_vsync_end; scalar_t__ crtc_vsync_start; scalar_t__ crtc_vblank_end; scalar_t__ crtc_vblank_start; scalar_t__ crtc_vtotal; scalar_t__ crtc_hsync_end; scalar_t__ crtc_hsync_start; scalar_t__ crtc_hblank_end; scalar_t__ crtc_hblank_start; scalar_t__ crtc_htotal; } ;
struct TYPE_8__ {int crtc_hdisplay; int crtc_vdisplay; } ;
struct drm_crtc {TYPE_4__ mode; TYPE_2__* primary; TYPE_1__* dev; } ;
struct ast_vbios_mode_info {struct ast_vbios_enhtable const* enh_table; int /*<<< orphan*/ * std_table; } ;
typedef  struct ast_vbios_enhtable {int flags; int refresh_rate; size_t refresh_rate_index; size_t mode_id; scalar_t__ vsync; scalar_t__ vfp; scalar_t__ vde; scalar_t__ vt; scalar_t__ hsync; scalar_t__ hfp; scalar_t__ hde; scalar_t__ ht; } const ast_vbios_enhtable ;
struct ast_private {scalar_t__ chip; } ;
struct TYPE_7__ {int* cpp; } ;
struct TYPE_6__ {struct drm_framebuffer* fb; } ;
struct TYPE_5__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ AST1180 ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int HBorder ; 
 size_t HiCModeIndex ; 
 int NHSync ; 
 int NVSync ; 
 int NewModeInfo ; 
 int PHSync ; 
 int PVSync ; 
 size_t TrueCModeIndex ; 
 int VBorder ; 
 size_t VGAModeIndex ; 
 int WideScreenMode ; 
 int /*<<< orphan*/  ast_set_index_reg (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 size_t drm_mode_vrefresh (struct drm_display_mode*) ; 
 struct ast_vbios_enhtable const* res_1024x768 ; 
 struct ast_vbios_enhtable const* res_1280x1024 ; 
 struct ast_vbios_enhtable const* res_1280x800 ; 
 struct ast_vbios_enhtable const* res_1360x768 ; 
 struct ast_vbios_enhtable const* res_1440x900 ; 
 struct ast_vbios_enhtable const* res_1600x1200 ; 
 struct ast_vbios_enhtable const* res_1600x900 ; 
 struct ast_vbios_enhtable const* res_1680x1050 ; 
 struct ast_vbios_enhtable const* res_1920x1080 ; 
 struct ast_vbios_enhtable const* res_1920x1200 ; 
 struct ast_vbios_enhtable const* res_640x480 ; 
 struct ast_vbios_enhtable const* res_800x600 ; 
 int /*<<< orphan*/ * vbios_stdtable ; 

__attribute__((used)) static bool ast_get_vbios_mode_info(struct drm_crtc *crtc, struct drm_display_mode *mode,
				    struct drm_display_mode *adjusted_mode,
				    struct ast_vbios_mode_info *vbios_mode)
{
	struct ast_private *ast = crtc->dev->dev_private;
	const struct drm_framebuffer *fb = crtc->primary->fb;
	u32 refresh_rate_index = 0, mode_id, color_index, refresh_rate;
	const struct ast_vbios_enhtable *best = NULL;
	u32 hborder, vborder;
	bool check_sync;

	switch (fb->format->cpp[0] * 8) {
	case 8:
		vbios_mode->std_table = &vbios_stdtable[VGAModeIndex];
		color_index = VGAModeIndex - 1;
		break;
	case 16:
		vbios_mode->std_table = &vbios_stdtable[HiCModeIndex];
		color_index = HiCModeIndex;
		break;
	case 24:
	case 32:
		vbios_mode->std_table = &vbios_stdtable[TrueCModeIndex];
		color_index = TrueCModeIndex;
		break;
	default:
		return false;
	}

	switch (crtc->mode.crtc_hdisplay) {
	case 640:
		vbios_mode->enh_table = &res_640x480[refresh_rate_index];
		break;
	case 800:
		vbios_mode->enh_table = &res_800x600[refresh_rate_index];
		break;
	case 1024:
		vbios_mode->enh_table = &res_1024x768[refresh_rate_index];
		break;
	case 1280:
		if (crtc->mode.crtc_vdisplay == 800)
			vbios_mode->enh_table = &res_1280x800[refresh_rate_index];
		else
			vbios_mode->enh_table = &res_1280x1024[refresh_rate_index];
		break;
	case 1360:
		vbios_mode->enh_table = &res_1360x768[refresh_rate_index];
		break;
	case 1440:
		vbios_mode->enh_table = &res_1440x900[refresh_rate_index];
		break;
	case 1600:
		if (crtc->mode.crtc_vdisplay == 900)
			vbios_mode->enh_table = &res_1600x900[refresh_rate_index];
		else
			vbios_mode->enh_table = &res_1600x1200[refresh_rate_index];
		break;
	case 1680:
		vbios_mode->enh_table = &res_1680x1050[refresh_rate_index];
		break;
	case 1920:
		if (crtc->mode.crtc_vdisplay == 1080)
			vbios_mode->enh_table = &res_1920x1080[refresh_rate_index];
		else
			vbios_mode->enh_table = &res_1920x1200[refresh_rate_index];
		break;
	default:
		return false;
	}

	refresh_rate = drm_mode_vrefresh(mode);
	check_sync = vbios_mode->enh_table->flags & WideScreenMode;
	do {
		const struct ast_vbios_enhtable *loop = vbios_mode->enh_table;

		while (loop->refresh_rate != 0xff) {
			if ((check_sync) &&
			    (((mode->flags & DRM_MODE_FLAG_NVSYNC)  &&
			      (loop->flags & PVSync))  ||
			     ((mode->flags & DRM_MODE_FLAG_PVSYNC)  &&
			      (loop->flags & NVSync))  ||
			     ((mode->flags & DRM_MODE_FLAG_NHSYNC)  &&
			      (loop->flags & PHSync))  ||
			     ((mode->flags & DRM_MODE_FLAG_PHSYNC)  &&
			      (loop->flags & NHSync)))) {
				loop++;
				continue;
			}
			if (loop->refresh_rate <= refresh_rate
			    && (!best || loop->refresh_rate > best->refresh_rate))
				best = loop;
			loop++;
		}
		if (best || !check_sync)
			break;
		check_sync = 0;
	} while (1);
	if (best)
		vbios_mode->enh_table = best;

	hborder = (vbios_mode->enh_table->flags & HBorder) ? 8 : 0;
	vborder = (vbios_mode->enh_table->flags & VBorder) ? 8 : 0;

	adjusted_mode->crtc_htotal = vbios_mode->enh_table->ht;
	adjusted_mode->crtc_hblank_start = vbios_mode->enh_table->hde + hborder;
	adjusted_mode->crtc_hblank_end = vbios_mode->enh_table->ht - hborder;
	adjusted_mode->crtc_hsync_start = vbios_mode->enh_table->hde + hborder +
		vbios_mode->enh_table->hfp;
	adjusted_mode->crtc_hsync_end = (vbios_mode->enh_table->hde + hborder +
					 vbios_mode->enh_table->hfp +
					 vbios_mode->enh_table->hsync);

	adjusted_mode->crtc_vtotal = vbios_mode->enh_table->vt;
	adjusted_mode->crtc_vblank_start = vbios_mode->enh_table->vde + vborder;
	adjusted_mode->crtc_vblank_end = vbios_mode->enh_table->vt - vborder;
	adjusted_mode->crtc_vsync_start = vbios_mode->enh_table->vde + vborder +
		vbios_mode->enh_table->vfp;
	adjusted_mode->crtc_vsync_end = (vbios_mode->enh_table->vde + vborder +
					 vbios_mode->enh_table->vfp +
					 vbios_mode->enh_table->vsync);

	refresh_rate_index = vbios_mode->enh_table->refresh_rate_index;
	mode_id = vbios_mode->enh_table->mode_id;

	if (ast->chip == AST1180) {
		/* TODO 1180 */
	} else {
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x8c, (u8)((color_index & 0xf) << 4));
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x8d, refresh_rate_index & 0xff);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x8e, mode_id & 0xff);

		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x91, 0x00);
		if (vbios_mode->enh_table->flags & NewModeInfo) {
			ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x91, 0xa8);
			ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x92,
					  fb->format->cpp[0] * 8);
			ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x93, adjusted_mode->clock / 1000);
			ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x94, adjusted_mode->crtc_hdisplay);
			ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x95, adjusted_mode->crtc_hdisplay >> 8);

			ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x96, adjusted_mode->crtc_vdisplay);
			ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x97, adjusted_mode->crtc_vdisplay >> 8);
		}
	}

	return true;


}