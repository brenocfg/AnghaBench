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
struct amdgpu_ring {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int amdgpu_debugfs_ring_init(struct amdgpu_device *adev,
				    struct amdgpu_ring *ring)
{
#if defined(CONFIG_DEBUG_FS)
	struct drm_minor *minor = adev->ddev->primary;
	struct dentry *ent, *root = minor->debugfs_root;
	char name[32];

	sprintf(name, "amdgpu_ring_%s", ring->name);

	ent = debugfs_create_file(name,
				  S_IFREG | S_IRUGO, root,
				  ring, &amdgpu_debugfs_ring_fops);
	if (!ent)
		return -ENOMEM;

	i_size_write(ent->d_inode, ring->ring_size + 12);
	ring->ent = ent;
#endif
	return 0;
}