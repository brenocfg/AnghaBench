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
typedef  int uint32_t ;
struct drm_display_mode {int hdisplay; int vdisplay; } ;
struct drm_connector {TYPE_1__* dev; } ;
struct ast_private {scalar_t__ chip; scalar_t__ support_wide_screen; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ AST1180 ; 
 scalar_t__ AST2100 ; 
 scalar_t__ AST2200 ; 
 scalar_t__ AST2300 ; 
 scalar_t__ AST2400 ; 
 scalar_t__ AST2500 ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int MODE_NOMODE ; 
 int MODE_OK ; 
 int ast_get_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static enum drm_mode_status ast_mode_valid(struct drm_connector *connector,
			  struct drm_display_mode *mode)
{
	struct ast_private *ast = connector->dev->dev_private;
	int flags = MODE_NOMODE;
	uint32_t jtemp;

	if (ast->support_wide_screen) {
		if ((mode->hdisplay == 1680) && (mode->vdisplay == 1050))
			return MODE_OK;
		if ((mode->hdisplay == 1280) && (mode->vdisplay == 800))
			return MODE_OK;
		if ((mode->hdisplay == 1440) && (mode->vdisplay == 900))
			return MODE_OK;
		if ((mode->hdisplay == 1360) && (mode->vdisplay == 768))
			return MODE_OK;
		if ((mode->hdisplay == 1600) && (mode->vdisplay == 900))
			return MODE_OK;

		if ((ast->chip == AST2100) || (ast->chip == AST2200) ||
		    (ast->chip == AST2300) || (ast->chip == AST2400) ||
		    (ast->chip == AST2500) || (ast->chip == AST1180)) {
			if ((mode->hdisplay == 1920) && (mode->vdisplay == 1080))
				return MODE_OK;

			if ((mode->hdisplay == 1920) && (mode->vdisplay == 1200)) {
				jtemp = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd1, 0xff);
				if (jtemp & 0x01)
					return MODE_NOMODE;
				else
					return MODE_OK;
			}
		}
	}
	switch (mode->hdisplay) {
	case 640:
		if (mode->vdisplay == 480) flags = MODE_OK;
		break;
	case 800:
		if (mode->vdisplay == 600) flags = MODE_OK;
		break;
	case 1024:
		if (mode->vdisplay == 768) flags = MODE_OK;
		break;
	case 1280:
		if (mode->vdisplay == 1024) flags = MODE_OK;
		break;
	case 1600:
		if (mode->vdisplay == 1200) flags = MODE_OK;
		break;
	default:
		return flags;
	}

	return flags;
}