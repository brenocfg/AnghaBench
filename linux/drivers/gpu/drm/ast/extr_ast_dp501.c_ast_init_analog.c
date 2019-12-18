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
typedef  int u32 ;
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int ast_read32 (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_set_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ast_write32 (struct ast_private*,int,int) ; 

__attribute__((used)) static void ast_init_analog(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;
	u32 data;

	/*
	 * Set DAC source to VGA mode in SCU2C via the P2A
	 * bridge. First configure the P2U to target the SCU
	 * in case it isn't at this stage.
	 */
	ast_write32(ast, 0xf004, 0x1e6e0000);
	ast_write32(ast, 0xf000, 0x1);

	/* Then unlock the SCU with the magic password */
	ast_write32(ast, 0x12000, 0x1688a8a8);
	ast_write32(ast, 0x12000, 0x1688a8a8);
	ast_write32(ast, 0x12000, 0x1688a8a8);

	/* Finally, clear bits [17:16] of SCU2c */
	data = ast_read32(ast, 0x1202c);
	data &= 0xfffcffff;
	ast_write32(ast, 0, data);

	/* Disable DVO */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa3, 0xcf, 0x00);
}