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
 size_t BPF_REG_1 ; 
 size_t BPF_REG_FP ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EMIT1 (int) ; 
 int /*<<< orphan*/  EMIT2 (int,int) ; 
 int /*<<< orphan*/  EMIT2_off32 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT3 (int,int,scalar_t__) ; 
 int /*<<< orphan*/  IA32_EAX ; 
 int /*<<< orphan*/  IA32_EBP ; 
 int /*<<< orphan*/  IA32_EBX ; 
 int PROLOGUE_SIZE ; 
 scalar_t__ SCRATCH_SIZE ; 
 int /*<<< orphan*/  STACK_SIZE ; 
 scalar_t__ STACK_VAR (int /*<<< orphan*/  const) ; 
 size_t TCALL_CNT ; 
 int add_1reg (int,int /*<<< orphan*/ ) ; 
 int add_2reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** bpf2ia32 ; 

__attribute__((used)) static void emit_prologue(u8 **pprog, u32 stack_depth)
{
	u8 *prog = *pprog;
	int cnt = 0;
	const u8 *r1 = bpf2ia32[BPF_REG_1];
	const u8 fplo = bpf2ia32[BPF_REG_FP][0];
	const u8 fphi = bpf2ia32[BPF_REG_FP][1];
	const u8 *tcc = bpf2ia32[TCALL_CNT];

	/* push ebp */
	EMIT1(0x55);
	/* mov ebp,esp */
	EMIT2(0x89, 0xE5);
	/* push edi */
	EMIT1(0x57);
	/* push esi */
	EMIT1(0x56);
	/* push ebx */
	EMIT1(0x53);

	/* sub esp,STACK_SIZE */
	EMIT2_off32(0x81, 0xEC, STACK_SIZE);
	/* sub ebp,SCRATCH_SIZE+12*/
	EMIT3(0x83, add_1reg(0xE8, IA32_EBP), SCRATCH_SIZE + 12);
	/* xor ebx,ebx */
	EMIT2(0x31, add_2reg(0xC0, IA32_EBX, IA32_EBX));

	/* Set up BPF prog stack base register */
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBP), STACK_VAR(fplo));
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBX), STACK_VAR(fphi));

	/* Move BPF_CTX (EAX) to BPF_REG_R1 */
	/* mov dword ptr [ebp+off],eax */
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(r1[0]));
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBX), STACK_VAR(r1[1]));

	/* Initialize Tail Count */
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBX), STACK_VAR(tcc[0]));
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBX), STACK_VAR(tcc[1]));

	BUILD_BUG_ON(cnt != PROLOGUE_SIZE);
	*pprog = prog;
}