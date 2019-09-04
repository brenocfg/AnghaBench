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
struct TYPE_6__ {TYPE_2__* sie_block; } ;
struct TYPE_4__ {int /*<<< orphan*/  exit_pei; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_1__ stat; } ;
struct TYPE_5__ {int ipa; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int handle_mvpg_pei (struct kvm_vcpu*) ; 
 int kvm_s390_handle_sigp_pei (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_partial_execution(struct kvm_vcpu *vcpu)
{
	vcpu->stat.exit_pei++;

	if (vcpu->arch.sie_block->ipa == 0xb254)	/* MVPG */
		return handle_mvpg_pei(vcpu);
	if (vcpu->arch.sie_block->ipa >> 8 == 0xae)	/* SIGP */
		return kvm_s390_handle_sigp_pei(vcpu);

	return -EOPNOTSUPP;
}