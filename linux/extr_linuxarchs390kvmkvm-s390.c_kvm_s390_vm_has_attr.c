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
struct kvm_device_attr {int group; int /*<<< orphan*/  attr; } ;
struct kvm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_cmma; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_S390_VM_CPU_MACHINE 147 
#define  KVM_S390_VM_CPU_MACHINE_FEAT 146 
#define  KVM_S390_VM_CPU_MACHINE_SUBFUNC 145 
#define  KVM_S390_VM_CPU_MODEL 144 
#define  KVM_S390_VM_CPU_PROCESSOR 143 
#define  KVM_S390_VM_CPU_PROCESSOR_FEAT 142 
#define  KVM_S390_VM_CPU_PROCESSOR_SUBFUNC 141 
#define  KVM_S390_VM_CRYPTO 140 
#define  KVM_S390_VM_CRYPTO_DISABLE_AES_KW 139 
#define  KVM_S390_VM_CRYPTO_DISABLE_DEA_KW 138 
#define  KVM_S390_VM_CRYPTO_ENABLE_AES_KW 137 
#define  KVM_S390_VM_CRYPTO_ENABLE_DEA_KW 136 
#define  KVM_S390_VM_MEM_CLR_CMMA 135 
#define  KVM_S390_VM_MEM_CTRL 134 
#define  KVM_S390_VM_MEM_ENABLE_CMMA 133 
#define  KVM_S390_VM_MEM_LIMIT_SIZE 132 
#define  KVM_S390_VM_MIGRATION 131 
#define  KVM_S390_VM_TOD 130 
#define  KVM_S390_VM_TOD_HIGH 129 
#define  KVM_S390_VM_TOD_LOW 128 
 TYPE_1__ sclp ; 

__attribute__((used)) static int kvm_s390_vm_has_attr(struct kvm *kvm, struct kvm_device_attr *attr)
{
	int ret;

	switch (attr->group) {
	case KVM_S390_VM_MEM_CTRL:
		switch (attr->attr) {
		case KVM_S390_VM_MEM_ENABLE_CMMA:
		case KVM_S390_VM_MEM_CLR_CMMA:
			ret = sclp.has_cmma ? 0 : -ENXIO;
			break;
		case KVM_S390_VM_MEM_LIMIT_SIZE:
			ret = 0;
			break;
		default:
			ret = -ENXIO;
			break;
		}
		break;
	case KVM_S390_VM_TOD:
		switch (attr->attr) {
		case KVM_S390_VM_TOD_LOW:
		case KVM_S390_VM_TOD_HIGH:
			ret = 0;
			break;
		default:
			ret = -ENXIO;
			break;
		}
		break;
	case KVM_S390_VM_CPU_MODEL:
		switch (attr->attr) {
		case KVM_S390_VM_CPU_PROCESSOR:
		case KVM_S390_VM_CPU_MACHINE:
		case KVM_S390_VM_CPU_PROCESSOR_FEAT:
		case KVM_S390_VM_CPU_MACHINE_FEAT:
		case KVM_S390_VM_CPU_MACHINE_SUBFUNC:
			ret = 0;
			break;
		/* configuring subfunctions is not supported yet */
		case KVM_S390_VM_CPU_PROCESSOR_SUBFUNC:
		default:
			ret = -ENXIO;
			break;
		}
		break;
	case KVM_S390_VM_CRYPTO:
		switch (attr->attr) {
		case KVM_S390_VM_CRYPTO_ENABLE_AES_KW:
		case KVM_S390_VM_CRYPTO_ENABLE_DEA_KW:
		case KVM_S390_VM_CRYPTO_DISABLE_AES_KW:
		case KVM_S390_VM_CRYPTO_DISABLE_DEA_KW:
			ret = 0;
			break;
		default:
			ret = -ENXIO;
			break;
		}
		break;
	case KVM_S390_VM_MIGRATION:
		ret = 0;
		break;
	default:
		ret = -ENXIO;
		break;
	}

	return ret;
}