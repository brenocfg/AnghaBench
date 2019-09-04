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
struct kvmppc_vcpu_e500 {unsigned int* pid; } ;
struct TYPE_4__ {TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int mas4; } ;

/* Variables and functions */
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

__attribute__((used)) static inline unsigned int get_tlbmiss_tid(struct kvm_vcpu *vcpu)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	unsigned int tidseld = (vcpu->arch.shared->mas4 >> 16) & 0xf;

	return vcpu_e500->pid[tidseld];
}