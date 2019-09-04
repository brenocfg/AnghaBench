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
struct TYPE_3__ {int /*<<< orphan*/  pgd; } ;
struct TYPE_4__ {TYPE_1__ gpa_mm; } ;
struct kvm {TYPE_2__ arch; } ;
typedef  int gfn_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int kvm_mips_mkclean_pgd (int /*<<< orphan*/ ,int,int) ; 

int kvm_mips_mkclean_gpa_pt(struct kvm *kvm, gfn_t start_gfn, gfn_t end_gfn)
{
	return kvm_mips_mkclean_pgd(kvm->arch.gpa_mm.pgd,
				    start_gfn << PAGE_SHIFT,
				    end_gfn << PAGE_SHIFT);
}