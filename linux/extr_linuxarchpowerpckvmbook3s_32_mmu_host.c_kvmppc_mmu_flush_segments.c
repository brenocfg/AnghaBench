#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvmppc_book3s_shadow_vcpu {int /*<<< orphan*/ * sr; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SR_INVALID ; 
 int /*<<< orphan*/  dprintk_sr (char*,int) ; 
 struct kvmppc_book3s_shadow_vcpu* svcpu_get (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  svcpu_put (struct kvmppc_book3s_shadow_vcpu*) ; 

void kvmppc_mmu_flush_segments(struct kvm_vcpu *vcpu)
{
	int i;
	struct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);

	dprintk_sr("MMU: flushing all segments (%d)\n", ARRAY_SIZE(svcpu->sr));
	for (i = 0; i < ARRAY_SIZE(svcpu->sr); i++)
		svcpu->sr[i] = SR_INVALID;

	svcpu_put(svcpu);
}