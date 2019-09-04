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
typedef  int /*<<< orphan*/  u64 ;
struct msr_data {unsigned int index; int host_initiated; int /*<<< orphan*/  data; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int kvm_set_msr (struct kvm_vcpu*,struct msr_data*) ; 

__attribute__((used)) static int do_set_msr(struct kvm_vcpu *vcpu, unsigned index, u64 *data)
{
	struct msr_data msr;

	msr.data = *data;
	msr.index = index;
	msr.host_initiated = true;
	return kvm_set_msr(vcpu, &msr);
}