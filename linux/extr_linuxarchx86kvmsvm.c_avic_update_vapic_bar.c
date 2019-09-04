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
typedef  int u64 ;
struct vcpu_svm {TYPE_2__* vmcb; } ;
struct TYPE_3__ {int avic_vapic_bar; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCB_AVIC ; 
 int VMCB_AVIC_APIC_BAR_MASK ; 
 int /*<<< orphan*/  mark_dirty (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void avic_update_vapic_bar(struct vcpu_svm *svm, u64 data)
{
	svm->vmcb->control.avic_vapic_bar = data & VMCB_AVIC_APIC_BAR_MASK;
	mark_dirty(svm->vmcb, VMCB_AVIC);
}