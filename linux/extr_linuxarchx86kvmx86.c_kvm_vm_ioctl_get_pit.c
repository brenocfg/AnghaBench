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
struct kvm_pit_state {int dummy; } ;
struct kvm_kpit_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  channels; } ;
struct TYPE_4__ {TYPE_1__* vpit; } ;
struct kvm {TYPE_2__ arch; } ;
struct TYPE_3__ {struct kvm_kpit_state pit_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  memcpy (struct kvm_pit_state*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_vm_ioctl_get_pit(struct kvm *kvm, struct kvm_pit_state *ps)
{
	struct kvm_kpit_state *kps = &kvm->arch.vpit->pit_state;

	BUILD_BUG_ON(sizeof(*ps) != sizeof(kps->channels));

	mutex_lock(&kps->lock);
	memcpy(ps, &kps->channels, sizeof(*ps));
	mutex_unlock(&kps->lock);
	return 0;
}