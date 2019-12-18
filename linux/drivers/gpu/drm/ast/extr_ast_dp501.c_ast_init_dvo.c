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
typedef  int u8 ;
typedef  int u32 ;
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {scalar_t__ chip; } ;

/* Variables and functions */
 scalar_t__ AST2300 ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int ast_get_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int ast_read32 (struct ast_private*,int) ; 
 int /*<<< orphan*/  ast_set_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ast_write32 (struct ast_private*,int,int) ; 

__attribute__((used)) static bool ast_init_dvo(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;
	u8 jreg;
	u32 data;
	ast_write32(ast, 0xf004, 0x1e6e0000);
	ast_write32(ast, 0xf000, 0x1);
	ast_write32(ast, 0x12000, 0x1688a8a8);

	jreg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);
	if (!(jreg & 0x80)) {
		/* Init SCU DVO Settings */
		data = ast_read32(ast, 0x12008);
		/* delay phase */
		data &= 0xfffff8ff;
		data |= 0x00000500;
		ast_write32(ast, 0x12008, data);

		if (ast->chip == AST2300) {
			data = ast_read32(ast, 0x12084);
			/* multi-pins for DVO single-edge */
			data |= 0xfffe0000;
			ast_write32(ast, 0x12084, data);

			data = ast_read32(ast, 0x12088);
			/* multi-pins for DVO single-edge */
			data |= 0x000fffff;
			ast_write32(ast, 0x12088, data);

			data = ast_read32(ast, 0x12090);
			/* multi-pins for DVO single-edge */
			data &= 0xffffffcf;
			data |= 0x00000020;
			ast_write32(ast, 0x12090, data);
		} else { /* AST2400 */
			data = ast_read32(ast, 0x12088);
			/* multi-pins for DVO single-edge */
			data |= 0x30000000;
			ast_write32(ast, 0x12088, data);

			data = ast_read32(ast, 0x1208c);
			/* multi-pins for DVO single-edge */
			data |= 0x000000cf;
			ast_write32(ast, 0x1208c, data);

			data = ast_read32(ast, 0x120a4);
			/* multi-pins for DVO single-edge */
			data |= 0xffff0000;
			ast_write32(ast, 0x120a4, data);

			data = ast_read32(ast, 0x120a8);
			/* multi-pins for DVO single-edge */
			data |= 0x0000000f;
			ast_write32(ast, 0x120a8, data);

			data = ast_read32(ast, 0x12094);
			/* multi-pins for DVO single-edge */
			data |= 0x00000002;
			ast_write32(ast, 0x12094, data);
		}
	}

	/* Force to DVO */
	data = ast_read32(ast, 0x1202c);
	data &= 0xfffbffff;
	ast_write32(ast, 0x1202c, data);

	/* Init VGA DVO Settings */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa3, 0xcf, 0x80);
	return true;
}