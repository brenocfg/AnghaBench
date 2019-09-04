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
struct kvmppc_xive {int dummy; } ;
struct kvm_device_attr {int group; int /*<<< orphan*/  addr; int /*<<< orphan*/  attr; } ;
struct kvm_device {struct kvmppc_xive* private; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_DEV_XICS_GRP_SOURCES 128 
 int xive_set_source (struct kvmppc_xive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xive_set_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
{
	struct kvmppc_xive *xive = dev->private;

	/* We honor the existing XICS ioctl */
	switch (attr->group) {
	case KVM_DEV_XICS_GRP_SOURCES:
		return xive_set_source(xive, attr->attr, attr->addr);
	}
	return -ENXIO;
}