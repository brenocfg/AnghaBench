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
struct TYPE_5__ {int /*<<< orphan*/  pgd; } ;
struct TYPE_4__ {int /*<<< orphan*/  pgd; } ;
struct TYPE_6__ {TYPE_2__ guest_user_mm; TYPE_1__ guest_kernel_mm; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mips_emul_free_gva_pt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_trap_emul_vcpu_uninit(struct kvm_vcpu *vcpu)
{
	kvm_mips_emul_free_gva_pt(vcpu->arch.guest_kernel_mm.pgd);
	kvm_mips_emul_free_gva_pt(vcpu->arch.guest_user_mm.pgd);
}