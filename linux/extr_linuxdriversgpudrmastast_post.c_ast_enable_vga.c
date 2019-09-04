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
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_MISC_PORT_WRITE ; 
 int /*<<< orphan*/  AST_IO_VGA_ENABLE_PORT ; 
 int /*<<< orphan*/  ast_io_write8 (struct ast_private*,int /*<<< orphan*/ ,int) ; 

void ast_enable_vga(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;

	ast_io_write8(ast, AST_IO_VGA_ENABLE_PORT, 0x01);
	ast_io_write8(ast, AST_IO_MISC_PORT_WRITE, 0x01);
}