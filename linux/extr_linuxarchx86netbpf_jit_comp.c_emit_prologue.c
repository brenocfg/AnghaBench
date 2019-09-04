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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int AUX_STACK_SPACE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EMIT1 (int) ; 
 int /*<<< orphan*/  EMIT2 (int,int) ; 
 int /*<<< orphan*/  EMIT3 (int,int,int) ; 
 int /*<<< orphan*/  EMIT3_off32 (int,int,int,int) ; 
 int /*<<< orphan*/  EMIT4 (int,int,int,int) ; 
 int PROLOGUE_SIZE ; 
 int round_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void emit_prologue(u8 **pprog, u32 stack_depth, bool ebpf_from_cbpf)
{
	u8 *prog = *pprog;
	int cnt = 0;

	/* push rbp */
	EMIT1(0x55);

	/* mov rbp,rsp */
	EMIT3(0x48, 0x89, 0xE5);

	/* sub rsp, rounded_stack_depth + AUX_STACK_SPACE */
	EMIT3_off32(0x48, 0x81, 0xEC,
		    round_up(stack_depth, 8) + AUX_STACK_SPACE);

	/* sub rbp, AUX_STACK_SPACE */
	EMIT4(0x48, 0x83, 0xED, AUX_STACK_SPACE);

	/* mov qword ptr [rbp+0],rbx */
	EMIT4(0x48, 0x89, 0x5D, 0);
	/* mov qword ptr [rbp+8],r13 */
	EMIT4(0x4C, 0x89, 0x6D, 8);
	/* mov qword ptr [rbp+16],r14 */
	EMIT4(0x4C, 0x89, 0x75, 16);
	/* mov qword ptr [rbp+24],r15 */
	EMIT4(0x4C, 0x89, 0x7D, 24);

	if (!ebpf_from_cbpf) {
		/*
		 * Clear the tail call counter (tail_call_cnt): for eBPF tail
		 * calls we need to reset the counter to 0. It's done in two
		 * instructions, resetting RAX register to 0, and moving it
		 * to the counter location.
		 */

		/* xor eax, eax */
		EMIT2(0x31, 0xc0);
		/* mov qword ptr [rbp+32], rax */
		EMIT4(0x48, 0x89, 0x45, 32);

		BUILD_BUG_ON(cnt != PROLOGUE_SIZE);
	}

	*pprog = prog;
}