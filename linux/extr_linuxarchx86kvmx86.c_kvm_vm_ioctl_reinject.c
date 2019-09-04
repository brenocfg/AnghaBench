#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvm_reinject_control {int /*<<< orphan*/  pit_reinject; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct kvm_pit {TYPE_2__ pit_state; } ;
struct TYPE_3__ {struct kvm_pit* vpit; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  kvm_pit_set_reinject (struct kvm_pit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_vm_ioctl_reinject(struct kvm *kvm,
				 struct kvm_reinject_control *control)
{
	struct kvm_pit *pit = kvm->arch.vpit;

	if (!pit)
		return -ENXIO;

	/* pit->pit_state.lock was overloaded to prevent userspace from getting
	 * an inconsistent state after running multiple KVM_REINJECT_CONTROL
	 * ioctls in parallel.  Use a separate lock if that ioctl isn't rare.
	 */
	mutex_lock(&pit->pit_state.lock);
	kvm_pit_set_reinject(pit, control->pit_reinject);
	mutex_unlock(&pit->pit_state.lock);

	return 0;
}