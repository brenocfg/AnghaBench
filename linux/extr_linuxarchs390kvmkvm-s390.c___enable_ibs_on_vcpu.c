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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_ibs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_DISABLE_IBS ; 
 int /*<<< orphan*/  KVM_REQ_ENABLE_IBS ; 
 int /*<<< orphan*/  kvm_check_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_sync_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 TYPE_1__ sclp ; 

__attribute__((used)) static void __enable_ibs_on_vcpu(struct kvm_vcpu *vcpu)
{
	if (!sclp.has_ibs)
		return;
	kvm_check_request(KVM_REQ_DISABLE_IBS, vcpu);
	kvm_s390_sync_request(KVM_REQ_ENABLE_IBS, vcpu);
}