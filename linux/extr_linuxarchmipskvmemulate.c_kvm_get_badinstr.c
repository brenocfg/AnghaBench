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
struct TYPE_2__ {int /*<<< orphan*/  host_cp0_badinstr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ cpu_has_badinstr ; 
 int kvm_get_inst (int /*<<< orphan*/ *,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 

int kvm_get_badinstr(u32 *opc, struct kvm_vcpu *vcpu, u32 *out)
{
	if (cpu_has_badinstr) {
		*out = vcpu->arch.host_cp0_badinstr;
		return 0;
	} else {
		return kvm_get_inst(opc, vcpu, out);
	}
}