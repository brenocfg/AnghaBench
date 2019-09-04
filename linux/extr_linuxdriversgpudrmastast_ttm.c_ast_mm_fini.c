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
struct drm_device {int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct ast_private {int /*<<< orphan*/  fb_mtrr; TYPE_1__ ttm; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_io_free_memtype_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ast_ttm_global_release (struct ast_private*) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 

void ast_mm_fini(struct ast_private *ast)
{
	struct drm_device *dev = ast->dev;

	ttm_bo_device_release(&ast->ttm.bdev);

	ast_ttm_global_release(ast);

	arch_phys_wc_del(ast->fb_mtrr);
	arch_io_free_memtype_wc(pci_resource_start(dev->pdev, 0),
				pci_resource_len(dev->pdev, 0));
}