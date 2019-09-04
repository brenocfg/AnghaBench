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
struct drm_display_mode {int dummy; } ;
struct drm_device {struct ast_private* dev_private; } ;
struct ast_vbios_mode_info {TYPE_1__* enh_table; } ;
struct ast_vbios_dclk_info {int param1; int param2; int param3; } ;
struct ast_private {scalar_t__ chip; } ;
struct TYPE_2__ {size_t dclk_index; } ;

/* Variables and functions */
 scalar_t__ AST2500 ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int /*<<< orphan*/  ast_set_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int,int) ; 
 struct ast_vbios_dclk_info* dclk_table ; 
 struct ast_vbios_dclk_info* dclk_table_ast2500 ; 

__attribute__((used)) static void ast_set_dclk_reg(struct drm_device *dev, struct drm_display_mode *mode,
			     struct ast_vbios_mode_info *vbios_mode)
{
	struct ast_private *ast = dev->dev_private;
	const struct ast_vbios_dclk_info *clk_info;

	if (ast->chip == AST2500)
		clk_info = &dclk_table_ast2500[vbios_mode->enh_table->dclk_index];
	else
		clk_info = &dclk_table[vbios_mode->enh_table->dclk_index];

	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xc0, 0x00, clk_info->param1);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xc1, 0x00, clk_info->param2);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xbb, 0x0f,
			       (clk_info->param3 & 0xc0) |
			       ((clk_info->param3 & 0x3) << 4));
}