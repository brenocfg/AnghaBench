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
struct kvm_vcpu {int dummy; } ;
struct kvm {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct kvm_vcpu* kvm_get_vcpu_by_id (struct kvm*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct kvm_vcpu *kvmppc_find_vcpu(struct kvm *kvm, int id)
{
	struct kvm_vcpu *ret;

	mutex_lock(&kvm->lock);
	ret = kvm_get_vcpu_by_id(kvm, id);
	mutex_unlock(&kvm->lock);
	return ret;
}