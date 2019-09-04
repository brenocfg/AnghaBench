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
struct radeon_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int radeon_ttm_debugfs_init(struct radeon_device *rdev)
{
#if defined(CONFIG_DEBUG_FS)
	unsigned count;

	struct drm_minor *minor = rdev->ddev->primary;
	struct dentry *ent, *root = minor->debugfs_root;

	ent = debugfs_create_file("radeon_vram", S_IFREG | S_IRUGO, root,
				  rdev, &radeon_ttm_vram_fops);
	if (IS_ERR(ent))
		return PTR_ERR(ent);
	rdev->mman.vram = ent;

	ent = debugfs_create_file("radeon_gtt", S_IFREG | S_IRUGO, root,
				  rdev, &radeon_ttm_gtt_fops);
	if (IS_ERR(ent))
		return PTR_ERR(ent);
	rdev->mman.gtt = ent;

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