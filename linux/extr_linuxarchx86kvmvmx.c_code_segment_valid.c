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
struct kvm_segment {unsigned int selector; int type; unsigned int dpl; int /*<<< orphan*/  present; int /*<<< orphan*/  s; scalar_t__ unusable; } ;

/* Variables and functions */
 unsigned int SEGMENT_RPL_MASK ; 
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 int VMX_AR_TYPE_ACCESSES_MASK ; 
 int VMX_AR_TYPE_CODE_MASK ; 
 int VMX_AR_TYPE_WRITEABLE_MASK ; 
 int /*<<< orphan*/  vmx_get_segment (struct kvm_vcpu*,struct kvm_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool code_segment_valid(struct kvm_vcpu *vcpu)
{
	struct kvm_segment cs;
	unsigned int cs_rpl;

	vmx_get_segment(vcpu, &cs, VCPU_SREG_CS);
	cs_rpl = cs.selector & SEGMENT_RPL_MASK;

	if (cs.unusable)
		return false;
	if (~cs.type & (VMX_AR_TYPE_CODE_MASK|VMX_AR_TYPE_ACCESSES_MASK))
		return false;
	if (!cs.s)
		return false;
	if (cs.type & VMX_AR_TYPE_WRITEABLE_MASK) {
		if (cs.dpl > cs_rpl)
			return false;
	} else {
		if (cs.dpl != cs_rpl)
			return false;
	}
	if (!cs.present)
		return false;

	/* TODO: Add Reserved field check, this'll require a new member in the kvm_segment_field structure */
	return true;
}