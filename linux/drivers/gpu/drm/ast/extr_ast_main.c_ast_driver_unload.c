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
struct drm_device {int /*<<< orphan*/  pdev; struct ast_private* dev_private; } ;
struct ast_private {scalar_t__ ioregs; scalar_t__ regs; struct ast_private* dp501_fw_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_IO_CRTC_PORT ; 
 scalar_t__ AST_IO_MM_OFFSET ; 
 int /*<<< orphan*/  ast_mm_fini (struct ast_private*) ; 
 int /*<<< orphan*/  ast_mode_fini (struct drm_device*) ; 
 int /*<<< orphan*/  ast_release_firmware (struct drm_device*) ; 
 int /*<<< orphan*/  ast_set_index_reg (struct ast_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct ast_private*) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,scalar_t__) ; 

void ast_driver_unload(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;

	/* enable standard VGA decode */
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa1, 0x04);

	ast_release_firmware(dev);
	kfree(ast->dp501_fw_addr);
	ast_mode_fini(dev);
	drm_mode_config_cleanup(dev);

	ast_mm_fini(ast);
	if (ast->ioregs != ast->regs + AST_IO_MM_OFFSET)
		pci_iounmap(dev->pdev, ast->ioregs);
	pci_iounmap(dev->pdev, ast->regs);
	kfree(ast);
}