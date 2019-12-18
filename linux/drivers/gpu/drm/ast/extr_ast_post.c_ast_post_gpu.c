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
typedef  int u32 ;
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {scalar_t__ config_mode; scalar_t__ chip; scalar_t__ tx_chip_type; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ AST2300 ; 
 scalar_t__ AST2400 ; 
 scalar_t__ AST2500 ; 
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 scalar_t__ AST_TX_NONE ; 
 int /*<<< orphan*/  ast_enable_mmio (struct drm_device*) ; 
 int /*<<< orphan*/  ast_enable_vga (struct drm_device*) ; 
 int /*<<< orphan*/  ast_init_3rdtx (struct drm_device*) ; 
 int /*<<< orphan*/  ast_init_dram_reg (struct drm_device*) ; 
 int /*<<< orphan*/  ast_open_key (struct ast_private*) ; 
 int /*<<< orphan*/  ast_post_chip_2300 (struct drm_device*) ; 
 int /*<<< orphan*/  ast_post_chip_2500 (struct drm_device*) ; 
 int /*<<< orphan*/  ast_set_def_ext_reg (struct drm_device*) ; 
 int /*<<< orphan*/  ast_set_index_reg_mask (struct ast_private*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ ast_use_p2a ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int) ; 

void ast_post_gpu(struct drm_device *dev)
{
	u32 reg;
	struct ast_private *ast = dev->dev_private;

	pci_read_config_dword(ast->dev->pdev, 0x04, &reg);
	reg |= 0x3;
	pci_write_config_dword(ast->dev->pdev, 0x04, reg);

	ast_enable_vga(dev);
	ast_open_key(ast);
	ast_enable_mmio(dev);
	ast_set_def_ext_reg(dev);

	if (ast->config_mode == ast_use_p2a) {
		if (ast->chip == AST2500)
			ast_post_chip_2500(dev);
		else if (ast->chip == AST2300 || ast->chip == AST2400)
			ast_post_chip_2300(dev);
		else
			ast_init_dram_reg(dev);

		ast_init_3rdtx(dev);
	} else {
		if (ast->tx_chip_type != AST_TX_NONE)
			ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa3, 0xcf, 0x80);	/* Enable DVO */
	}
}