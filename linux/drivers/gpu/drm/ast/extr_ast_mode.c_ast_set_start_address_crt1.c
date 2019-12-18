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
typedef  int u32 ;
struct drm_crtc {TYPE_1__* dev; } ;
struct ast_private {int dummy; } ;
struct TYPE_2__ {struct ast_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 int /*<<< orphan*/  ast_set_index_reg (struct ast_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ast_set_start_address_crt1(struct drm_crtc *crtc, unsigned offset)
{
	struct ast_private *ast = crtc->dev->dev_private;
	u32 addr;

	addr = offset >> 2;
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x0d, (u8)(addr & 0xff));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x0c, (u8)((addr >> 8) & 0xff));
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xaf, (u8)((addr >> 16) & 0xff));

}