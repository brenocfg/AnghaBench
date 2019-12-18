#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_minor {struct dentry* debugfs_root; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct amdgpu_ring {char* name; struct dentry* ent; scalar_t__ ring_size; } ;
struct amdgpu_device {TYPE_1__* ddev; } ;
struct TYPE_2__ {struct drm_minor* primary; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int /*<<< orphan*/  amdgpu_debugfs_ring_fops ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct amdgpu_ring*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_size_write (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

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