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
struct kvm_vcpu {int /*<<< orphan*/  debugfs_dentry; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_has_tsc_control ; 
 int /*<<< orphan*/  vcpu_tsc_offset_fops ; 
 int /*<<< orphan*/  vcpu_tsc_scaling_fops ; 
 int /*<<< orphan*/  vcpu_tsc_scaling_frac_fops ; 

int kvm_arch_create_vcpu_debugfs(struct kvm_vcpu *vcpu)
{
	struct dentry *ret;

	ret = debugfs_create_file("tsc-offset", 0444,
							vcpu->debugfs_dentry,
							vcpu, &vcpu_tsc_offset_fops);
	if (!ret)
		return -ENOMEM;

	if (kvm_has_tsc_control) {
		ret = debugfs_create_file("tsc-scaling-ratio", 0444,
							vcpu->debugfs_dentry,
							vcpu, &vcpu_tsc_scaling_fops);
		if (!ret)
			return -ENOMEM;
		ret = debugfs_create_file("tsc-scaling-ratio-frac-bits", 0444,
							vcpu->debugfs_dentry,
							vcpu, &vcpu_tsc_scaling_frac_fops);
		if (!ret)
			return -ENOMEM;

	}

	return 0;
}