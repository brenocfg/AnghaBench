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
typedef  int /*<<< orphan*/  u32 ;
struct x86_emulate_ctxt {int dummy; } ;
struct msr_data {int host_initiated; int /*<<< orphan*/  data; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int kvm_get_msr (int /*<<< orphan*/ ,struct msr_data*) ; 

__attribute__((used)) static int emulator_get_msr(struct x86_emulate_ctxt *ctxt,
			    u32 msr_index, u64 *pdata)
{
	struct msr_data msr;
	int r;

	msr.index = msr_index;
	msr.host_initiated = false;
	r = kvm_get_msr(emul_to_vcpu(ctxt), &msr);
	if (r)
		return r;

	*pdata = msr.data;
	return 0;
}