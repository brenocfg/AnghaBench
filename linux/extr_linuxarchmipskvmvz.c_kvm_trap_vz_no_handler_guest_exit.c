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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int CAUSEF_BD ; 
 int EMULATE_FAIL ; 
 int /*<<< orphan*/  kvm_err (char*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_get_badinstr (int*,struct kvm_vcpu*,int*) ; 
 int /*<<< orphan*/  read_gc0_status () ; 

__attribute__((used)) static enum emulation_result kvm_trap_vz_no_handler_guest_exit(u32 gexccode,
							u32 cause,
							u32 *opc,
							struct kvm_vcpu *vcpu)
{
	u32 inst;

	/*
	 *  Fetch the instruction.
	 */
	if (cause & CAUSEF_BD)
		opc += 1;
	kvm_get_badinstr(opc, vcpu, &inst);

	kvm_err("Guest Exception Code: %d not yet handled @ PC: %p, inst: 0x%08x  Status: %#x\n",
		gexccode, opc, inst, read_gc0_status());

	return EMULATE_FAIL;
}