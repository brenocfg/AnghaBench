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
struct openpic {TYPE_1__* dst; } ;
struct TYPE_4__ {size_t irq_cpu_id; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/ * vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

void kvmppc_mpic_disconnect_vcpu(struct openpic *opp, struct kvm_vcpu *vcpu)
{
	BUG_ON(!opp->dst[vcpu->arch.irq_cpu_id].vcpu);

	opp->dst[vcpu->arch.irq_cpu_id].vcpu = NULL;
}