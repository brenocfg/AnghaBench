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
typedef  int /*<<< orphan*/  u32 ;
struct kvmppc_xics {scalar_t__ kvm; } ;
struct TYPE_2__ {scalar_t__ irq_type; } ;
struct kvm_vcpu {scalar_t__ kvm; TYPE_1__ arch; } ;
struct kvm_device {int /*<<< orphan*/ * ops; struct kvmppc_xics* private; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 scalar_t__ KVMPPC_IRQ_XICS ; 
 int /*<<< orphan*/  kvm_xics_ops ; 
 int kvmppc_xics_create_icp (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

int kvmppc_xics_connect_vcpu(struct kvm_device *dev, struct kvm_vcpu *vcpu,
			     u32 xcpu)
{
	struct kvmppc_xics *xics = dev->private;
	int r = -EBUSY;

	if (dev->ops != &kvm_xics_ops)
		return -EPERM;
	if (xics->kvm != vcpu->kvm)
		return -EPERM;
	if (vcpu->arch.irq_type)
		return -EBUSY;

	r = kvmppc_xics_create_icp(vcpu, xcpu);
	if (!r)
		vcpu->arch.irq_type = KVMPPC_IRQ_XICS;

	return r;
}