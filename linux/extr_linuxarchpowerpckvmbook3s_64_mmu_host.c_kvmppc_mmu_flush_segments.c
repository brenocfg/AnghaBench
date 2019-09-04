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
struct kvmppc_book3s_shadow_vcpu {TYPE_1__* slb; scalar_t__ slb_max; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ esid; } ;

/* Variables and functions */
 struct kvmppc_book3s_shadow_vcpu* svcpu_get (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  svcpu_put (struct kvmppc_book3s_shadow_vcpu*) ; 

void kvmppc_mmu_flush_segments(struct kvm_vcpu *vcpu)
{
	struct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	svcpu->slb_max = 0;
	svcpu->slb[0].esid = 0;
	svcpu_put(svcpu);
}