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
typedef  int /*<<< orphan*/  u8 ;
struct drm_crtc {TYPE_1__* dev; } ;
struct ast_private {int next_cursor; int /*<<< orphan*/  cursor_cache; } ;
struct ast_crtc {int offset_x; int offset_y; } ;
struct TYPE_2__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 int AST_HWC_SIGNATURE_SIZE ; 
 int AST_HWC_SIGNATURE_X ; 
 int AST_HWC_SIGNATURE_Y ; 
 int AST_HWC_SIZE ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int /*<<< orphan*/  ast_set_index_reg (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ast_show_cursor (struct drm_crtc*) ; 
 int /*<<< orphan*/ * drm_gem_vram_kmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_vram_of_gem (int /*<<< orphan*/ ) ; 
 struct ast_crtc* to_ast_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ast_cursor_move(struct drm_crtc *crtc,
			   int x, int y)
{
	struct ast_crtc *ast_crtc = to_ast_crtc(crtc);
	struct ast_private *ast = crtc->dev->dev_private;
	int x_offset, y_offset;
	u8 *sig;

	sig = drm_gem_vram_kmap(drm_gem_vram_of_gem(ast->cursor_cache),
				false, NULL);
	sig += (AST_HWC_SIZE + AST_HWC_SIGNATURE_SIZE)*ast->next_cursor + AST_HWC_SIZE;
	writel(x, sig + AST_HWC_SIGNATURE_X);
	writel(y, sig + AST_HWC_SIGNATURE_Y);

	x_offset = ast_crtc->offset_x;
	y_offset = ast_crtc->offset_y;
	if (x < 0) {
		x_offset = (-x) + ast_crtc->offset_x;
		x = 0;
	}

	if (y < 0) {
		y_offset = (-y) + ast_crtc->offset_y;
		y = 0;
	}
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc2, x_offset);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc3, y_offset);
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc4, (x & 0xff));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc5, ((x >> 8) & 0x0f));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc6, (y & 0xff));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xc7, ((y >> 8) & 0x07));

	/* dummy write to fire HWC */
	ast_show_cursor(crtc);

	return 0;
}