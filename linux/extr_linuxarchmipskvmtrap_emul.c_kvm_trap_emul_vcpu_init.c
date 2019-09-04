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
struct mm_struct {void* pgd; } ;
struct TYPE_2__ {struct mm_struct guest_user_mm; struct mm_struct guest_kernel_mm; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* pgd_alloc (struct mm_struct*) ; 
 int /*<<< orphan*/  pgd_free (struct mm_struct*,void*) ; 

__attribute__((used)) static int kvm_trap_emul_vcpu_init(struct kvm_vcpu *vcpu)
{
	struct mm_struct *kern_mm = &vcpu->arch.guest_kernel_mm;
	struct mm_struct *user_mm = &vcpu->arch.guest_user_mm;

	/*
	 * Allocate GVA -> HPA page tables.
	 * MIPS doesn't use the mm_struct pointer argument.
	 */
	kern_mm->pgd = pgd_alloc(kern_mm);
	if (!kern_mm->pgd)
		return -ENOMEM;

	user_mm->pgd = pgd_alloc(user_mm);
	if (!user_mm->pgd) {
		pgd_free(kern_mm, kern_mm->pgd);
		return -ENOMEM;
	}

	return 0;
}