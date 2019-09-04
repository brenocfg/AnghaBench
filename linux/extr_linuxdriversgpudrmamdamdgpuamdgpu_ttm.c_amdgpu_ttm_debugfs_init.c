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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int amdgpu_ttm_debugfs_init(struct amdgpu_device *adev)
{
#if defined(CONFIG_DEBUG_FS)
	unsigned count;

	struct drm_minor *minor = adev->ddev->primary;
	struct dentry *ent, *root = minor->debugfs_root;

	for (count = 0; count < ARRAY_SIZE(ttm_debugfs_entries); count++) {
		ent = debugfs_create_file(
				ttm_debugfs_entries[count].name,
				S_IFREG | S_IRUGO, root,
				adev,
				ttm_debugfs_entries[count].fops);
		if (IS_ERR(ent))
			return PTR_ERR(ent);
		if (ttm_debugfs_entries[count].domain == TTM_PL_VRAM)
			i_size_write(ent->d_inode, adev->gmc.mc_vram_size);
		else if (ttm_debugfs_entries[count].domain == TTM_PL_TT)
			i_size_write(ent->d_inode, adev->gmc.gart_size);
		adev->mman.debugfs_entries[count] = ent;
	}

	count = ARRAY_SIZE(amdgpu_ttm_debugfs_list);

#ifdef CONFIG_SWIOTLB
	if (!(adev->need_swiotlb && swiotlb_nr_tbl()))
		--count;
#endif

	return amdgpu_debugfs_add_files(adev, amdgpu_ttm_debugfs_list, count);
#else
	return 0;
#endif
}