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
struct sys_reg_params {int /*<<< orphan*/  is_write; } ;
struct sys_reg_desc {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM64_HAS_STAGE2_FWB ; 
 int /*<<< orphan*/  cpus_have_const_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_way_flush (struct kvm_vcpu*) ; 
 int read_from_write_only (struct kvm_vcpu*,struct sys_reg_params*,struct sys_reg_desc const*) ; 

__attribute__((used)) static bool access_dcsw(struct kvm_vcpu *vcpu,
			struct sys_reg_params *p,
			const struct sys_reg_desc *r)
{
	if (!p->is_write)
		return read_from_write_only(vcpu, p, r);

	/*
	 * Only track S/W ops if we don't have FWB. It still indicates
	 * that the guest is a bit broken (S/W operations should only
	 * be done by firmware, knowing that there is only a single
	 * CPU left in the system, and certainly not from non-secure
	 * software).
	 */
	if (!cpus_have_const_cap(ARM64_HAS_STAGE2_FWB))
		kvm_set_way_flush(vcpu);

	return true;
}