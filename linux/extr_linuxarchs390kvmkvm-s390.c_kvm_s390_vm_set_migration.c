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
struct kvm_device_attr {int attr; } ;
struct kvm {int /*<<< orphan*/  slots_lock; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_S390_VM_MIGRATION_START 129 
#define  KVM_S390_VM_MIGRATION_STOP 128 
 int kvm_s390_vm_start_migration (struct kvm*) ; 
 int kvm_s390_vm_stop_migration (struct kvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_s390_vm_set_migration(struct kvm *kvm,
				     struct kvm_device_attr *attr)
{
	int res = -ENXIO;

	mutex_lock(&kvm->slots_lock);
	switch (attr->attr) {
	case KVM_S390_VM_MIGRATION_START:
		res = kvm_s390_vm_start_migration(kvm);
		break;
	case KVM_S390_VM_MIGRATION_STOP:
		res = kvm_s390_vm_stop_migration(kvm);
		break;
	default:
		break;
	}
	mutex_unlock(&kvm->slots_lock);

	return res;
}