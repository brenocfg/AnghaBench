#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cr11; int /*<<< orphan*/  cr10; int /*<<< orphan*/  cr9; int /*<<< orphan*/  cr0; } ;
struct TYPE_5__ {TYPE_1__ guestdbg; TYPE_3__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_6__ {int /*<<< orphan*/ * gcr; } ;

/* Variables and functions */

void kvm_s390_restore_guest_per_regs(struct kvm_vcpu *vcpu)
{
	vcpu->arch.sie_block->gcr[0] = vcpu->arch.guestdbg.cr0;
	vcpu->arch.sie_block->gcr[9] = vcpu->arch.guestdbg.cr9;
	vcpu->arch.sie_block->gcr[10] = vcpu->arch.guestdbg.cr10;
	vcpu->arch.sie_block->gcr[11] = vcpu->arch.guestdbg.cr11;
}