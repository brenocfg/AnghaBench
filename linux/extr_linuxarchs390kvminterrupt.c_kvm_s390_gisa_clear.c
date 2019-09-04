#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct kvm_s390_gisa {int dummy; } ;
struct TYPE_4__ {TYPE_2__* gisa; } ;
struct kvm {TYPE_1__ arch; } ;
struct TYPE_5__ {scalar_t__ next_alert; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_EVENT (struct kvm*,int,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void kvm_s390_gisa_clear(struct kvm *kvm)
{
	if (kvm->arch.gisa) {
		memset(kvm->arch.gisa, 0, sizeof(struct kvm_s390_gisa));
		kvm->arch.gisa->next_alert = (u32)(u64)kvm->arch.gisa;
		VM_EVENT(kvm, 3, "gisa 0x%pK cleared", kvm->arch.gisa);
	}
}