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
struct TYPE_3__ {int /*<<< orphan*/  root_hpa; } ;
struct TYPE_4__ {TYPE_1__ mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_init_mmu (struct kvm_vcpu*,int) ; 

void kvm_mmu_setup(struct kvm_vcpu *vcpu)
{
	MMU_WARN_ON(VALID_PAGE(vcpu->arch.mmu.root_hpa));

	/*
	 * kvm_mmu_setup() is called only on vCPU initialization.  
	 * Therefore, no need to reset mmu roots as they are not yet
	 * initialized.
	 */
	kvm_init_mmu(vcpu, false);
}