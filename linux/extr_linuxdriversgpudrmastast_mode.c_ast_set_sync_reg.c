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
struct drm_display_mode {int dummy; } ;
struct drm_device {struct ast_private* dev_private; } ;
struct ast_vbios_mode_info {TYPE_1__* enh_table; } ;
struct ast_private {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_MISC_PORT_READ ; 
 int /*<<< orphan*/  AST_IO_MISC_PORT_WRITE ; 
 int NHSync ; 
 int NVSync ; 
 int ast_io_read8 (struct ast_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ast_io_write8 (struct ast_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ast_set_sync_reg(struct drm_device *dev, struct drm_display_mode *mode,
		      struct ast_vbios_mode_info *vbios_mode)
{
	struct ast_private *ast = dev->dev_private;
	u8 jreg;

	jreg  = ast_io_read8(ast, AST_IO_MISC_PORT_READ);
	jreg &= ~0xC0;
	if (vbios_mode->enh_table->flags & NVSync) jreg |= 0x80;
	if (vbios_mode->enh_table->flags & NHSync) jreg |= 0x40;
	ast_io_write8(ast, AST_IO_MISC_PORT_WRITE, jreg);
}