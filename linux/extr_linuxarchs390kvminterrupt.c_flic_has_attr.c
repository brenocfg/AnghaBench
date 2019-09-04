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
struct kvm_device_attr {int group; } ;
struct kvm_device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_DEV_FLIC_ADAPTER_MODIFY 138 
#define  KVM_DEV_FLIC_ADAPTER_REGISTER 137 
#define  KVM_DEV_FLIC_AIRQ_INJECT 136 
#define  KVM_DEV_FLIC_AISM 135 
#define  KVM_DEV_FLIC_AISM_ALL 134 
#define  KVM_DEV_FLIC_APF_DISABLE_WAIT 133 
#define  KVM_DEV_FLIC_APF_ENABLE 132 
#define  KVM_DEV_FLIC_CLEAR_IO_IRQ 131 
#define  KVM_DEV_FLIC_CLEAR_IRQS 130 
#define  KVM_DEV_FLIC_ENQUEUE 129 
#define  KVM_DEV_FLIC_GET_ALL_IRQS 128 

__attribute__((used)) static int flic_has_attr(struct kvm_device *dev,
			     struct kvm_device_attr *attr)
{
	switch (attr->group) {
	case KVM_DEV_FLIC_GET_ALL_IRQS:
	case KVM_DEV_FLIC_ENQUEUE:
	case KVM_DEV_FLIC_CLEAR_IRQS:
	case KVM_DEV_FLIC_APF_ENABLE:
	case KVM_DEV_FLIC_APF_DISABLE_WAIT:
	case KVM_DEV_FLIC_ADAPTER_REGISTER:
	case KVM_DEV_FLIC_ADAPTER_MODIFY:
	case KVM_DEV_FLIC_CLEAR_IO_IRQ:
	case KVM_DEV_FLIC_AISM:
	case KVM_DEV_FLIC_AIRQ_INJECT:
	case KVM_DEV_FLIC_AISM_ALL:
		return 0;
	}
	return -ENXIO;
}