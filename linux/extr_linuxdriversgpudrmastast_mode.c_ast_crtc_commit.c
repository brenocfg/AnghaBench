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
struct ast_private {int dummy; } ;
struct TYPE_2__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_SEQ_PORT ; 
 int /*<<< orphan*/  ast_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  ast_set_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ast_crtc_commit(struct drm_crtc *crtc)
{
	struct ast_private *ast = crtc->dev->dev_private;
	ast_set_index_reg_mask(ast, AST_IO_SEQ_PORT, 0x1, 0xdf, 0);
	ast_crtc_load_lut(crtc);
}