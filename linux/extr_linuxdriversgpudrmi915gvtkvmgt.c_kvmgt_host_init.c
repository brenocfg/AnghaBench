#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct attribute_group {int dummy; } ;
struct attribute {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_gvt_attrs ) (struct attribute***,struct attribute_group***) ;} ;
struct TYPE_4__ {struct attribute_group** supported_type_groups; } ;

/* Variables and functions */
 int EFAULT ; 
 TYPE_3__* intel_gvt_ops ; 
 TYPE_1__ intel_vgpu_ops ; 
 int mdev_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct attribute***,struct attribute_group***) ; 

__attribute__((used)) static int kvmgt_host_init(struct device *dev, void *gvt, const void *ops)
{
	struct attribute **kvm_type_attrs;
	struct attribute_group **kvm_vgpu_type_groups;

	intel_gvt_ops = ops;
	if (!intel_gvt_ops->get_gvt_attrs(&kvm_type_attrs,
			&kvm_vgpu_type_groups))
		return -EFAULT;
	intel_vgpu_ops.supported_type_groups = kvm_vgpu_type_groups;

	return mdev_register_device(dev, &intel_vgpu_ops);
}