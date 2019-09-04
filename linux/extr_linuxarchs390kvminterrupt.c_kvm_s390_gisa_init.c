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
struct TYPE_5__ {int /*<<< orphan*/ * gisa; TYPE_1__* sie_page2; } ;
struct kvm {TYPE_2__ arch; } ;
struct TYPE_6__ {scalar_t__ aiv; } ;
struct TYPE_4__ {int /*<<< orphan*/  gisa; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_EVENT (struct kvm*,int,char*,int /*<<< orphan*/ *) ; 
 TYPE_3__ css_general_characteristics ; 
 int /*<<< orphan*/  kvm_s390_gisa_clear (struct kvm*) ; 

void kvm_s390_gisa_init(struct kvm *kvm)
{
	if (css_general_characteristics.aiv) {
		kvm->arch.gisa = &kvm->arch.sie_page2->gisa;
		VM_EVENT(kvm, 3, "gisa 0x%pK initialized", kvm->arch.gisa);
		kvm_s390_gisa_clear(kvm);
	}
}