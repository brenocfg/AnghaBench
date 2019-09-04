#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* sie_block; } ;
struct kvm_vcpu {TYPE_5__* kvm; TYPE_1__ arch; } ;
struct TYPE_7__ {int /*<<< orphan*/  crycbd; scalar_t__ dea_kw; scalar_t__ aes_kw; } ;
struct TYPE_8__ {TYPE_2__ crypto; } ;
struct TYPE_10__ {TYPE_3__ arch; } ;
struct TYPE_9__ {int ecb3; int /*<<< orphan*/  crycbd; } ;

/* Variables and functions */
 int ECB3_AES ; 
 int ECB3_DEA ; 
 int /*<<< orphan*/  test_kvm_facility (TYPE_5__*,int) ; 

__attribute__((used)) static void kvm_s390_vcpu_crypto_setup(struct kvm_vcpu *vcpu)
{
	if (!test_kvm_facility(vcpu->kvm, 76))
		return;

	vcpu->arch.sie_block->ecb3 &= ~(ECB3_AES | ECB3_DEA);

	if (vcpu->kvm->arch.crypto.aes_kw)
		vcpu->arch.sie_block->ecb3 |= ECB3_AES;
	if (vcpu->kvm->arch.crypto.dea_kw)
		vcpu->arch.sie_block->ecb3 |= ECB3_DEA;

	vcpu->arch.sie_block->crycbd = vcpu->kvm->arch.crypto.crycbd;
}