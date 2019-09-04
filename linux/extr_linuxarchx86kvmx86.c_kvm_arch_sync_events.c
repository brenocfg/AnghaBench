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
struct TYPE_2__ {int /*<<< orphan*/  kvmclock_update_work; int /*<<< orphan*/  kvmclock_sync_work; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_free_pit (struct kvm*) ; 

void kvm_arch_sync_events(struct kvm *kvm)
{
	cancel_delayed_work_sync(&kvm->arch.kvmclock_sync_work);
	cancel_delayed_work_sync(&kvm->arch.kvmclock_update_work);
	kvm_free_pit(kvm);
}