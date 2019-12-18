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
struct ttm_bo_global {int /*<<< orphan*/  device_list; } ;
struct ttm_bo_driver {int dummy; } ;
struct ttm_bo_device {int need_dma32; int /*<<< orphan*/  device_list; struct ttm_bo_global* glob; struct address_space* dev_mapping; int /*<<< orphan*/  ddestroy; int /*<<< orphan*/  wq; int /*<<< orphan*/  vma_manager; int /*<<< orphan*/  man; struct ttm_bo_driver* driver; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET_SIZE ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET_START ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TTM_PL_SYSTEM ; 
 int /*<<< orphan*/  drm_vma_offset_manager_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_delayed_workqueue ; 
 struct ttm_bo_global ttm_bo_glob ; 
 int ttm_bo_global_init () ; 
 int /*<<< orphan*/  ttm_bo_global_release () ; 
 int ttm_bo_init_mm (struct ttm_bo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_global_mutex ; 
 scalar_t__ unlikely (int) ; 

int ttm_bo_device_init(struct ttm_bo_device *bdev,
		       struct ttm_bo_driver *driver,
		       struct address_space *mapping,
		       bool need_dma32)
{
	struct ttm_bo_global *glob = &ttm_bo_glob;
	int ret;

	ret = ttm_bo_global_init();
	if (ret)
		return ret;

	bdev->driver = driver;

	memset(bdev->man, 0, sizeof(bdev->man));

	/*
	 * Initialize the system memory buffer type.
	 * Other types need to be driver / IOCTL initialized.
	 */
	ret = ttm_bo_init_mm(bdev, TTM_PL_SYSTEM, 0);
	if (unlikely(ret != 0))
		goto out_no_sys;

	drm_vma_offset_manager_init(&bdev->vma_manager,
				    DRM_FILE_PAGE_OFFSET_START,
				    DRM_FILE_PAGE_OFFSET_SIZE);
	INIT_DELAYED_WORK(&bdev->wq, ttm_bo_delayed_workqueue);
	INIT_LIST_HEAD(&bdev->ddestroy);
	bdev->dev_mapping = mapping;
	bdev->glob = glob;
	bdev->need_dma32 = need_dma32;
	mutex_lock(&ttm_global_mutex);
	list_add_tail(&bdev->device_list, &glob->device_list);
	mutex_unlock(&ttm_global_mutex);

	return 0;
out_no_sys:
	ttm_bo_global_release();
	return ret;
}