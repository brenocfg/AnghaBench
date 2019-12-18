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
struct TYPE_8__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_6__ {TYPE_1__* anon_inode; } ;
struct qxl_device {unsigned int surfaceram_size; scalar_t__ vram_size; TYPE_4__ mman; TYPE_3__* rom; TYPE_2__ ddev; } ;
struct TYPE_7__ {unsigned int ram_header_offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  TTM_PL_PRIV ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  qxl_bo_driver ; 
 int ttm_bo_device_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ttm_bo_init_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

int qxl_ttm_init(struct qxl_device *qdev)
{
	int r;
	int num_io_pages; /* != rom->num_io_pages, we include surface0 */

	/* No others user of address space so set it to 0 */
	r = ttm_bo_device_init(&qdev->mman.bdev,
			       &qxl_bo_driver,
			       qdev->ddev.anon_inode->i_mapping,
			       false);
	if (r) {
		DRM_ERROR("failed initializing buffer object driver(%d).\n", r);
		return r;
	}
	/* NOTE: this includes the framebuffer (aka surface 0) */
	num_io_pages = qdev->rom->ram_header_offset / PAGE_SIZE;
	r = ttm_bo_init_mm(&qdev->mman.bdev, TTM_PL_VRAM,
			   num_io_pages);
	if (r) {
		DRM_ERROR("Failed initializing VRAM heap.\n");
		return r;
	}
	r = ttm_bo_init_mm(&qdev->mman.bdev, TTM_PL_PRIV,
			   qdev->surfaceram_size / PAGE_SIZE);
	if (r) {
		DRM_ERROR("Failed initializing Surfaces heap.\n");
		return r;
	}
	DRM_INFO("qxl: %uM of VRAM memory size\n",
		 (unsigned int)qdev->vram_size / (1024 * 1024));
	DRM_INFO("qxl: %luM of IO pages memory ready (VRAM domain)\n",
		 ((unsigned int)num_io_pages * PAGE_SIZE) / (1024 * 1024));
	DRM_INFO("qxl: %uM of Surface memory size\n",
		 (unsigned int)qdev->surfaceram_size / (1024 * 1024));
	return 0;
}