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
struct drm_vma_offset_manager {int dummy; } ;
struct drm_device {struct drm_vma_offset_manager* vma_offset_manager; int /*<<< orphan*/  object_name_idr; int /*<<< orphan*/  object_name_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET_SIZE ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET_START ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_vma_offset_manager_init (struct drm_vma_offset_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init_base (int /*<<< orphan*/ *,int) ; 
 struct drm_vma_offset_manager* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int
drm_gem_init(struct drm_device *dev)
{
	struct drm_vma_offset_manager *vma_offset_manager;

	mutex_init(&dev->object_name_lock);
	idr_init_base(&dev->object_name_idr, 1);

	vma_offset_manager = kzalloc(sizeof(*vma_offset_manager), GFP_KERNEL);
	if (!vma_offset_manager) {
		DRM_ERROR("out of memory\n");
		return -ENOMEM;
	}

	dev->vma_offset_manager = vma_offset_manager;
	drm_vma_offset_manager_init(vma_offset_manager,
				    DRM_FILE_PAGE_OFFSET_START,
				    DRM_FILE_PAGE_OFFSET_SIZE);

	return 0;
}