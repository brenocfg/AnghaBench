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
struct kvm_vcpu {int dummy; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int kvm_mips_bad_load (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct kvm_run*,struct kvm_vcpu*) ; 
 int kvm_mips_bad_store (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct kvm_run*,struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_mips_bad_access(u32 cause, u32 *opc, struct kvm_run *run,
			       struct kvm_vcpu *vcpu, bool store)
{
	if (store)
		return kvm_mips_bad_store(cause, opc, run, vcpu);
	else
		return kvm_mips_bad_load(cause, opc, run, vcpu);
}