#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* gtt; void* vram; } ;
struct radeon_device {scalar_t__ need_swiotlb; TYPE_2__ mman; TYPE_1__* ddev; } ;
struct drm_minor {struct dentry* debugfs_root; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {struct drm_minor* primary; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 void* debugfs_create_file (char*,int,struct dentry*,struct radeon_device*,int /*<<< orphan*/ *) ; 
 int radeon_debugfs_add_files (struct radeon_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  radeon_ttm_debugfs_list ; 
 int /*<<< orphan*/  radeon_ttm_gtt_fops ; 
 int /*<<< orphan*/  radeon_ttm_vram_fops ; 
 scalar_t__ swiotlb_nr_tbl () ; 

__attribute__((used)) static int radeon_ttm_debugfs_init(struct radeon_device *rdev)
{
#if defined(CONFIG_DEBUG_FS)
	unsigned count;

	struct drm_minor *minor = rdev->ddev->primary;
	struct dentry *root = minor->debugfs_root;

	rdev->mman.vram = debugfs_create_file("radeon_vram", S_IFREG | S_IRUGO,
					      root, rdev,
					      &radeon_ttm_vram_fops);

	rdev->mman.gtt = debugfs_create_file("radeon_gtt", S_IFREG | S_IRUGO,
					     root, rdev, &radeon_ttm_gtt_fops);

	count = ARRAY_SIZE(radeon_ttm_debugfs_list);

#ifdef CONFIG_SWIOTLB
	if (!(rdev->need_swiotlb && swiotlb_nr_tbl()))
		--count;
#endif

	return radeon_debugfs_add_files(rdev, radeon_ttm_debugfs_list, count);
#else

	return 0;
#endif
}