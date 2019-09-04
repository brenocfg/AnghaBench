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
struct drm_crtc {TYPE_1__* dev; } ;
struct ast_private {scalar_t__ chip; int /*<<< orphan*/  tx_chip_type; } ;
struct TYPE_2__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ AST1180 ; 
 int /*<<< orphan*/  AST_IO_SEQ_PORT ; 
 int /*<<< orphan*/  AST_TX_DP501 ; 
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  ast_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  ast_set_dp501_video_output (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ast_set_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void ast_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct ast_private *ast = crtc->dev->dev_private;

	if (ast->chip == AST1180)
		return;

	switch (mode) {
	case DRM_MODE_DPMS_ON:
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
		ast_set_index_reg_mask(ast, AST_IO_SEQ_PORT, 0x1, 0xdf, 0);
		if (ast->tx_chip_type == AST_TX_DP501)
			ast_set_dp501_video_output(crtc->dev, 1);
		ast_crtc_load_lut(crtc);
		break;
	case DRM_MODE_DPMS_OFF:
		if (ast->tx_chip_type == AST_TX_DP501)
			ast_set_dp501_video_output(crtc->dev, 0);
		ast_set_index_reg_mask(ast, AST_IO_SEQ_PORT, 0x1, 0xdf, 0x20);
		break;
	}
}