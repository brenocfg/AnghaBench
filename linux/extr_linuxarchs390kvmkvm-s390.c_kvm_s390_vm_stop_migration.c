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
struct TYPE_2__ {scalar_t__ use_cmma; scalar_t__ migration_mode; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_STOP_MIGRATION ; 
 int /*<<< orphan*/  kvm_s390_sync_request_broadcast (struct kvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_s390_vm_stop_migration(struct kvm *kvm)
{
	/* migration mode already disabled */
	if (!kvm->arch.migration_mode)
		return 0;
	kvm->arch.migration_mode = 0;
	if (kvm->arch.use_cmma)
		kvm_s390_sync_request_broadcast(kvm, KVM_REQ_STOP_MIGRATION);
	return 0;
}