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
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int eca; } ;

/* Variables and functions */
 int ECA_SII ; 
 int /*<<< orphan*/  ipte_unlock_siif (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  ipte_unlock_simple (struct kvm_vcpu*) ; 

void ipte_unlock(struct kvm_vcpu *vcpu)
{
	if (vcpu->arch.sie_block->eca & ECA_SII)
		ipte_unlock_siif(vcpu);
	else
		ipte_unlock_simple(vcpu);
}