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
struct intel_vgpu {int id; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  active; TYPE_1__* gvt; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  debugfs_root; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dentry* debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct intel_vgpu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  vgpu_mmio_diff_fops ; 
 int /*<<< orphan*/  vgpu_scan_nonprivbb_fops ; 

int intel_gvt_debugfs_add_vgpu(struct intel_vgpu *vgpu)
{
	struct dentry *ent;
	char name[10] = "";

	sprintf(name, "vgpu%d", vgpu->id);
	vgpu->debugfs = debugfs_create_dir(name, vgpu->gvt->debugfs_root);
	if (!vgpu->debugfs)
		return -ENOMEM;

	ent = debugfs_create_bool("active", 0444, vgpu->debugfs,
				  &vgpu->active);
	if (!ent)
		return -ENOMEM;

	ent = debugfs_create_file("mmio_diff", 0444, vgpu->debugfs,
				  vgpu, &vgpu_mmio_diff_fops);
	if (!ent)
		return -ENOMEM;

	ent = debugfs_create_file("scan_nonprivbb", 0644, vgpu->debugfs,
				 vgpu, &vgpu_scan_nonprivbb_fops);
	if (!ent)
		return -ENOMEM;

	return 0;
}