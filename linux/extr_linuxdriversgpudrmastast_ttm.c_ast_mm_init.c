#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ttm_bo_device {int dummy; } ;
struct drm_device {int /*<<< orphan*/  pdev; TYPE_4__* anon_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  object; } ;
struct TYPE_6__ {TYPE_1__ ref; } ;
struct TYPE_7__ {TYPE_2__ bo_global_ref; struct ttm_bo_device bdev; } ;
struct ast_private {int vram_size; int /*<<< orphan*/  fb_mtrr; TYPE_3__ ttm; struct drm_device* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  arch_io_reserve_memtype_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_phys_wc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ast_bo_driver ; 
 int ast_ttm_global_init (struct ast_private*) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttm_bo_device_init (struct ttm_bo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ttm_bo_init_mm (struct ttm_bo_device*,int /*<<< orphan*/ ,int) ; 

int ast_mm_init(struct ast_private *ast)
{
	int ret;
	struct drm_device *dev = ast->dev;
	struct ttm_bo_device *bdev = &ast->ttm.bdev;

	ret = ast_ttm_global_init(ast);
	if (ret)
		return ret;

	ret = ttm_bo_device_init(&ast->ttm.bdev,
				 ast->ttm.bo_global_ref.ref.object,
				 &ast_bo_driver,
				 dev->anon_inode->i_mapping,
				 DRM_FILE_PAGE_OFFSET,
				 true);
	if (ret) {
		DRM_ERROR("Error initialising bo driver; %d\n", ret);
		return ret;
	}

	ret = ttm_bo_init_mm(bdev, TTM_PL_VRAM,
			     ast->vram_size >> PAGE_SHIFT);
	if (ret) {
		DRM_ERROR("Failed ttm VRAM init: %d\n", ret);
		return ret;
	}

	arch_io_reserve_memtype_wc(pci_resource_start(dev->pdev, 0),
				   pci_resource_len(dev->pdev, 0));
	ast->fb_mtrr = arch_phys_wc_add(pci_resource_start(dev->pdev, 0),
					pci_resource_len(dev->pdev, 0));

	return 0;
}