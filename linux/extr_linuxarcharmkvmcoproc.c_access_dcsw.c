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
struct kvm_vcpu {int dummy; } ;
struct coproc_reg {int dummy; } ;
struct coproc_params {int /*<<< orphan*/  is_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_set_way_flush (struct kvm_vcpu*) ; 
 int read_from_write_only (struct kvm_vcpu*,struct coproc_params const*) ; 

__attribute__((used)) static bool access_dcsw(struct kvm_vcpu *vcpu,
			const struct coproc_params *p,
			const struct coproc_reg *r)
{
	if (!p->is_write)
		return read_from_write_only(vcpu, p);

	kvm_set_way_flush(vcpu);
	return true;
}