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
struct kvm_segment {int selector; int type; int /*<<< orphan*/  present; scalar_t__ unusable; } ;

/* Variables and functions */
 int SEGMENT_TI_MASK ; 
 int /*<<< orphan*/  VCPU_SREG_LDTR ; 
 int /*<<< orphan*/  vmx_get_segment (struct kvm_vcpu*,struct kvm_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ldtr_valid(struct kvm_vcpu *vcpu)
{
	struct kvm_segment ldtr;

	vmx_get_segment(vcpu, &ldtr, VCPU_SREG_LDTR);

	if (ldtr.unusable)
		return true;
	if (ldtr.selector & SEGMENT_TI_MASK)	/* TI = 1 */
		return false;
	if (ldtr.type != 2)
		return false;
	if (!ldtr.present)
		return false;

	return true;
}