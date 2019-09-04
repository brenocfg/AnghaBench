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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu_hv_synic {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct kvm_vcpu_hv_synic* synic_get (struct kvm*,int /*<<< orphan*/ ) ; 
 int synic_set_irq (struct kvm_vcpu_hv_synic*,int /*<<< orphan*/ ) ; 

int kvm_hv_synic_set_irq(struct kvm *kvm, u32 vpidx, u32 sint)
{
	struct kvm_vcpu_hv_synic *synic;

	synic = synic_get(kvm, vpidx);
	if (!synic)
		return -EINVAL;

	return synic_set_irq(synic, sint);
}