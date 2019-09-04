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
struct TYPE_3__ {int /*<<< orphan*/  tlb_flush; } ;
struct kvm_vcpu {TYPE_1__ stat; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* tlb_flush ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void kvm_vcpu_flush_tlb(struct kvm_vcpu *vcpu, bool invalidate_gpa)
{
	++vcpu->stat.tlb_flush;
	kvm_x86_ops->tlb_flush(vcpu, invalidate_gpa);
}