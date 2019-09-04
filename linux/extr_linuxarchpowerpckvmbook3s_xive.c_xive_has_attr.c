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
struct kvm_device_attr {int group; int /*<<< orphan*/  attr; } ;
struct kvm_device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KVMPPC_XICS_FIRST_IRQ ; 
 int /*<<< orphan*/  KVMPPC_XICS_NR_IRQS ; 
#define  KVM_DEV_XICS_GRP_SOURCES 128 

__attribute__((used)) static int xive_has_attr(struct kvm_device *dev, struct kvm_device_attr *attr)
{
	/* We honor the same limits as XICS, at least for now */
	switch (attr->group) {
	case KVM_DEV_XICS_GRP_SOURCES:
		if (attr->attr >= KVMPPC_XICS_FIRST_IRQ &&
		    attr->attr < KVMPPC_XICS_NR_IRQS)
			return 0;
		break;
	}
	return -ENXIO;
}