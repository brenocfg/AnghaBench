#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct virtio_gpu_device {TYPE_3__ mman; TYPE_2__* ddev; } ;
struct TYPE_5__ {TYPE_1__* anon_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  TTM_PL_TT ; 
 int ttm_bo_device_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 
 int ttm_bo_init_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_gpu_bo_driver ; 

int virtio_gpu_ttm_init(struct virtio_gpu_device *vgdev)
{
	int r;

	/* No others user of address space so set it to 0 */
	r = ttm_bo_device_init(&vgdev->mman.bdev,
			       &virtio_gpu_bo_driver,
			       vgdev->ddev->anon_inode->i_mapping,
			       false);
	if (r) {
		DRM_ERROR("failed initializing buffer object driver(%d).\n", r);
		goto err_dev_init;
	}

	r = ttm_bo_init_mm(&vgdev->mman.bdev, TTM_PL_TT, 0);
	if (r) {
		DRM_ERROR("Failed initializing GTT heap.\n");
		goto err_mm_init;
	}
	return 0;

err_mm_init:
	ttm_bo_device_release(&vgdev->mman.bdev);
err_dev_init:
	return r;
}