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
typedef  int ulong ;
typedef  int u32 ;

/* Variables and functions */
 int KVM_INST_B_MASK ; 
 int KVM_INST_B_MAX ; 
 int /*<<< orphan*/  KVM_RT_30 ; 
 int /*<<< orphan*/  flush_icache_range (int,int) ; 
 int get_rt (int) ; 
 int* kvm_alloc (int) ; 
 int /*<<< orphan*/  kvm_emulate_mtmsrd ; 
 size_t kvm_emulate_mtmsrd_branch_offs ; 
 int kvm_emulate_mtmsrd_len ; 
 size_t kvm_emulate_mtmsrd_orig_ins_offs ; 
 size_t kvm_emulate_mtmsrd_reg_offs ; 
 int /*<<< orphan*/  kvm_patch_ins_b (int*,int) ; 
 int /*<<< orphan*/  kvm_patch_ins_ll (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvm_patching_worked ; 
 int /*<<< orphan*/  magic_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scratch1 ; 
 int /*<<< orphan*/  scratch2 ; 

__attribute__((used)) static void kvm_patch_ins_mtmsrd(u32 *inst, u32 rt)
{
	u32 *p;
	int distance_start;
	int distance_end;
	ulong next_inst;

	p = kvm_alloc(kvm_emulate_mtmsrd_len * 4);
	if (!p)
		return;

	/* Find out where we are and put everything there */
	distance_start = (ulong)p - (ulong)inst;
	next_inst = ((ulong)inst + 4);
	distance_end = next_inst - (ulong)&p[kvm_emulate_mtmsrd_branch_offs];

	/* Make sure we only write valid b instructions */
	if (distance_start > KVM_INST_B_MAX) {
		kvm_patching_worked = false;
		return;
	}

	/* Modify the chunk to fit the invocation */
	memcpy(p, kvm_emulate_mtmsrd, kvm_emulate_mtmsrd_len * 4);
	p[kvm_emulate_mtmsrd_branch_offs] |= distance_end & KVM_INST_B_MASK;
	switch (get_rt(rt)) {
	case 30:
		kvm_patch_ins_ll(&p[kvm_emulate_mtmsrd_reg_offs],
				 magic_var(scratch2), KVM_RT_30);
		break;
	case 31:
		kvm_patch_ins_ll(&p[kvm_emulate_mtmsrd_reg_offs],
				 magic_var(scratch1), KVM_RT_30);
		break;
	default:
		p[kvm_emulate_mtmsrd_reg_offs] |= rt;
		break;
	}

	p[kvm_emulate_mtmsrd_orig_ins_offs] = *inst;
	flush_icache_range((ulong)p, (ulong)p + kvm_emulate_mtmsrd_len * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_start);
}