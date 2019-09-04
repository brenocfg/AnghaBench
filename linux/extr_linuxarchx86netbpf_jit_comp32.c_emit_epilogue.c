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
 size_t BPF_REG_0 ; 
 int /*<<< orphan*/  EMIT1 (int) ; 
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IA32_EAX ; 
 int /*<<< orphan*/  IA32_EBP ; 
 int /*<<< orphan*/  IA32_EBX ; 
 int /*<<< orphan*/  IA32_EDI ; 
 int /*<<< orphan*/  IA32_EDX ; 
 int /*<<< orphan*/  IA32_ESI ; 
 int SCRATCH_SIZE ; 
 int STACK_VAR (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  add_1reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_2reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** bpf2ia32 ; 

__attribute__((used)) static void emit_epilogue(u8 **pprog, u32 stack_depth)
{
	u8 *prog = *pprog;
	const u8 *r0 = bpf2ia32[BPF_REG_0];
	int cnt = 0;

	/* mov eax,dword ptr [ebp+off]*/
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(r0[0]));
	/* mov edx,dword ptr [ebp+off]*/
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX), STACK_VAR(r0[1]));

	/* add ebp,SCRATCH_SIZE+12*/
	EMIT3(0x83, add_1reg(0xC0, IA32_EBP), SCRATCH_SIZE + 12);

	/* mov ebx,dword ptr [ebp-12]*/
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EBX), -12);
	/* mov esi,dword ptr [ebp-8]*/
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ESI), -8);
	/* mov edi,dword ptr [ebp-4]*/
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDI), -4);

	EMIT1(0xC9); /* leave */
	EMIT1(0xC3); /* ret */
	*pprog = prog;
}