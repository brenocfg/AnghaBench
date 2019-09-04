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
typedef  int u8 ;
struct drm_framebuffer {TYPE_3__* format; } ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc {TYPE_2__* primary; TYPE_1__* dev; } ;
struct ast_vbios_mode_info {int dummy; } ;
struct ast_private {scalar_t__ chip; } ;
struct TYPE_6__ {int* cpp; } ;
struct TYPE_5__ {struct drm_framebuffer* fb; } ;
struct TYPE_4__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ AST1100 ; 
 scalar_t__ AST2100 ; 
 scalar_t__ AST2150 ; 
 scalar_t__ AST2200 ; 
 scalar_t__ AST2300 ; 
 scalar_t__ AST2400 ; 
 scalar_t__ AST2500 ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int /*<<< orphan*/  ast_set_index_reg (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ast_set_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void ast_set_ext_reg(struct drm_crtc *crtc, struct drm_display_mode *mode,
			     struct ast_vbios_mode_info *vbios_mode)
{
	struct ast_private *ast = crtc->dev->dev_private;
	const struct drm_framebuffer *fb = crtc->primary->fb;
	u8 jregA0 = 0, jregA3 = 0, jregA8 = 0;

	switch (fb->format->cpp[0] * 8) {
	case 8:
		jregA0 = 0x70;
		jregA3 = 0x01;
		jregA8 = 0x00;
		break;
	case 15:
	case 16:
		jregA0 = 0x70;
		jregA3 = 0x04;
		jregA8 = 0x02;
		break;
	case 32:
		jregA0 = 0x70;
		jregA3 = 0x08;
		jregA8 = 0x02;
		break;
	}

	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa0, 0x8f, jregA0);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa3, 0xf0, jregA3);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa8, 0xfd, jregA8);

	/* Set Threshold */
	if (ast->chip == AST2300 || ast->chip == AST2400 ||
	    ast->chip == AST2500) {
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa7, 0x78);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa6, 0x60);
	} else if (ast->chip == AST2100 ||
		   ast->chip == AST1100 ||
		   ast->chip == AST2200 ||
		   ast->chip == AST2150) {
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa7, 0x3f);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa6, 0x2f);
	} else {
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa7, 0x2f);
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa6, 0x1f);
	}
}