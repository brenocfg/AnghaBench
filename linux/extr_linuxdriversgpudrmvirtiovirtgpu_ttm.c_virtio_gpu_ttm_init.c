#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  object; } ;
struct TYPE_9__ {TYPE_5__ ref; } ;
struct TYPE_8__ {int /*<<< orphan*/  bdev; TYPE_4__ bo_global_ref; } ;
struct virtio_gpu_device {TYPE_3__ mman; TYPE_2__* ddev; } ;
struct TYPE_7__ {TYPE_1__* anon_inode; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET ; 
 int /*<<< orphan*/  TTM_PL_TT ; 
 int ttm_bo_device_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 
 int ttm_bo_init_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_gpu_bo_driver ; 
 int /*<<< orphan*/  virtio_gpu_ttm_global_fini (struct virtio_gpu_device*) ; 
 int virtio_gpu_ttm_global_init (struct virtio_gpu_device*) ; 

int virtio_gpu_ttm_init(struct virtio_gpu_device *vgdev)
{
	int r;

	r = virtio_gpu_ttm_global_init(vgdev);
	if (r)
		return r;
	/* No others user of address space so set it to 0 */
	r = ttm_bo_device_init(&vgdev->mman.bdev,
			       vgdev->mman.bo_global_ref.ref.object,
			       &virtio_gpu_bo_driver,
			       vgdev->ddev->anon_inode->i_mapping,
			       DRM_FILE_PAGE_OFFSET, 0);
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
	virtio_gpu_ttm_global_fini(vgdev);
	return r;
}