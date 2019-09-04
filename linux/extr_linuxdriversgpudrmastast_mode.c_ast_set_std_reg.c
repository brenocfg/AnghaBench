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
typedef  int u8 ;
typedef  int u32 ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct ast_vbios_stdtable {int misc; int* seq; int* crtc; int* ar; int* gr; } ;
struct ast_vbios_mode_info {struct ast_vbios_stdtable* std_table; } ;
struct ast_private {int dummy; } ;
struct TYPE_2__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_AR_PORT_WRITE ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int /*<<< orphan*/  AST_IO_GR_PORT ; 
 int /*<<< orphan*/  AST_IO_INPUT_STATUS1_READ ; 
 int /*<<< orphan*/  AST_IO_MISC_PORT_WRITE ; 
 int /*<<< orphan*/  AST_IO_SEQ_PORT ; 
 int ast_io_read8 (struct ast_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ast_io_write8 (struct ast_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ast_set_index_reg (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ast_set_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void ast_set_std_reg(struct drm_crtc *crtc, struct drm_display_mode *mode,
			    struct ast_vbios_mode_info *vbios_mode)
{
	struct ast_private *ast = crtc->dev->dev_private;
	const struct ast_vbios_stdtable *stdtable;
	u32 i;
	u8 jreg;

	stdtable = vbios_mode->std_table;

	jreg = stdtable->misc;
	ast_io_write8(ast, AST_IO_MISC_PORT_WRITE, jreg);

	/* Set SEQ */
	ast_set_index_reg(ast, AST_IO_SEQ_PORT, 0x00, 0x03);
	for (i = 0; i < 4; i++) {
		jreg = stdtable->seq[i];
		if (!i)
			jreg |= 0x20;
		ast_set_index_reg(ast, AST_IO_SEQ_PORT, (i + 1) , jreg);
	}

	/* Set CRTC */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x11, 0x7f, 0x00);
	for (i = 0; i < 25; i++)
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, i, stdtable->crtc[i]);

	/* set AR */
	jreg = ast_io_read8(ast, AST_IO_INPUT_STATUS1_READ);
	for (i = 0; i < 20; i++) {
		jreg = stdtable->ar[i];
		ast_io_write8(ast, AST_IO_AR_PORT_WRITE, (u8)i);
		ast_io_write8(ast, AST_IO_AR_PORT_WRITE, jreg);
	}
	ast_io_write8(ast, AST_IO_AR_PORT_WRITE, 0x14);
	ast_io_write8(ast, AST_IO_AR_PORT_WRITE, 0x00);

	jreg = ast_io_read8(ast, AST_IO_INPUT_STATUS1_READ);
	ast_io_write8(ast, AST_IO_AR_PORT_WRITE, 0x20);

	/* Set GR */
	for (i = 0; i < 9; i++)
		ast_set_index_reg(ast, AST_IO_GR_PORT, i, stdtable->gr[i]);
}