#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct drm_minor {struct dentry* debugfs_root; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct TYPE_10__ {struct dentry** debugfs_entries; } ;
struct TYPE_9__ {int /*<<< orphan*/  gart_size; int /*<<< orphan*/  mc_vram_size; } ;
struct amdgpu_device {scalar_t__ need_swiotlb; TYPE_3__ mman; TYPE_2__ gmc; TYPE_1__* ddev; } ;
struct TYPE_11__ {scalar_t__ domain; int /*<<< orphan*/  fops; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {struct drm_minor* primary; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_4__*) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 scalar_t__ TTM_PL_TT ; 
 scalar_t__ TTM_PL_VRAM ; 
 int amdgpu_debugfs_add_files (struct amdgpu_device*,TYPE_4__*,unsigned int) ; 
 TYPE_4__* amdgpu_ttm_debugfs_list ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,struct dentry*,struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ swiotlb_nr_tbl () ; 
 TYPE_4__* ttm_debugfs_entries ; 

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