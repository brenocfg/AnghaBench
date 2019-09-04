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
struct kvm {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_S390_VM_CPU_MODEL 132 
#define  KVM_S390_VM_CRYPTO 131 
#define  KVM_S390_VM_MEM_CTRL 130 
#define  KVM_S390_VM_MIGRATION 129 
#define  KVM_S390_VM_TOD 128 
 int kvm_s390_set_cpu_model (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_set_mem_control (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_set_tod (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_vm_set_crypto (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_vm_set_migration (struct kvm*,struct kvm_device_attr*) ; 

__attribute__((used)) static int kvm_s390_vm_set_attr(struct kvm *kvm, struct kvm_device_attr *attr)
{
	int ret;

	switch (attr->group) {
	case KVM_S390_VM_MEM_CTRL:
		ret = kvm_s390_set_mem_control(kvm, attr);
		break;
	case KVM_S390_VM_TOD:
		ret = kvm_s390_set_tod(kvm, attr);
		break;
	case KVM_S390_VM_CPU_MODEL:
		ret = kvm_s390_set_cpu_model(kvm, attr);
		break;
	case KVM_S390_VM_CRYPTO:
		ret = kvm_s390_vm_set_crypto(kvm, attr);
		break;
	case KVM_S390_VM_MIGRATION:
		ret = kvm_s390_vm_set_migration(kvm, attr);
		break;
	default:
		ret = -ENXIO;
		break;
	}

	return ret;
}