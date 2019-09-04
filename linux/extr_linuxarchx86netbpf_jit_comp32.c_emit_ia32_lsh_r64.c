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

/* Variables and functions */
 int /*<<< orphan*/  EMIT1_off32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT2_off32 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IA32_EAX ; 
 int /*<<< orphan*/  IA32_EBP ; 
 int /*<<< orphan*/  IA32_EBX ; 
 int /*<<< orphan*/  IA32_ECX ; 
 int /*<<< orphan*/  IA32_EDX ; 
 int IA32_JAE ; 
 int STACK_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_1reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_2reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 
 scalar_t__ is_imm8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_label (int,int) ; 
 int /*<<< orphan*/  src_lo ; 

__attribute__((used)) static inline void emit_ia32_lsh_r64(const u8 dst[], const u8 src[],
				     bool dstk, bool sstk, u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;
	static int jmp_label1 = -1;
	static int jmp_label2 = -1;
	static int jmp_label3 = -1;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	}

	if (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(src_lo));
	else
		/* mov ecx,src_lo */
		EMIT2(0x8B, add_2reg(0xC0, src_lo, IA32_ECX));

	/* cmp ecx,32 */
	EMIT3(0x83, add_1reg(0xF8, IA32_ECX), 32);
	/* Jumps when >= 32 */
	if (is_imm8(jmp_label(jmp_label1, 2)))
		EMIT2(IA32_JAE, jmp_label(jmp_label1, 2));
	else
		EMIT2_off32(0x0F, IA32_JAE + 0x10, jmp_label(jmp_label1, 6));

	/* < 32 */
	/* shl dreg_hi,cl */
	EMIT2(0xD3, add_1reg(0xE0, dreg_hi));
	/* mov ebx,dreg_lo */
	EMIT2(0x8B, add_2reg(0xC0, dreg_lo, IA32_EBX));
	/* shl dreg_lo,cl */
	EMIT2(0xD3, add_1reg(0xE0, dreg_lo));

	/* IA32_ECX = -IA32_ECX + 32 */
	/* neg ecx */
	EMIT2(0xF7, add_1reg(0xD8, IA32_ECX));
	/* add ecx,32 */
	EMIT3(0x83, add_1reg(0xC0, IA32_ECX), 32);

	/* shr ebx,cl */
	EMIT2(0xD3, add_1reg(0xE8, IA32_EBX));
	/* or dreg_hi,ebx */
	EMIT2(0x09, add_2reg(0xC0, dreg_hi, IA32_EBX));

	/* goto out; */
	if (is_imm8(jmp_label(jmp_label3, 2)))
		EMIT2(0xEB, jmp_label(jmp_label3, 2));
	else
		EMIT1_off32(0xE9, jmp_label(jmp_label3, 5));

	/* >= 32 */
	if (jmp_label1 == -1)
		jmp_label1 = cnt;

	/* cmp ecx,64 */
	EMIT3(0x83, add_1reg(0xF8, IA32_ECX), 64);
	/* Jumps when >= 64 */
	if (is_imm8(jmp_label(jmp_label2, 2)))
		EMIT2(IA32_JAE, jmp_label(jmp_label2, 2));
	else
		EMIT2_off32(0x0F, IA32_JAE + 0x10, jmp_label(jmp_label2, 6));

	/* >= 32 && < 64 */
	/* sub ecx,32 */
	EMIT3(0x83, add_1reg(0xE8, IA32_ECX), 32);
	/* shl dreg_lo,cl */
	EMIT2(0xD3, add_1reg(0xE0, dreg_lo));
	/* mov dreg_hi,dreg_lo */
	EMIT2(0x89, add_2reg(0xC0, dreg_hi, dreg_lo));

	/* xor dreg_lo,dreg_lo */
	EMIT2(0x33, add_2reg(0xC0, dreg_lo, dreg_lo));

	/* goto out; */
	if (is_imm8(jmp_label(jmp_label3, 2)))
		EMIT2(0xEB, jmp_label(jmp_label3, 2));
	else
		EMIT1_off32(0xE9, jmp_label(jmp_label3, 5));

	/* >= 64 */
	if (jmp_label2 == -1)
		jmp_label2 = cnt;
	/* xor dreg_lo,dreg_lo */
	EMIT2(0x33, add_2reg(0xC0, dreg_lo, dreg_lo));
	/* xor dreg_hi,dreg_hi */
	EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));

	if (jmp_label3 == -1)
		jmp_label3 = cnt;

	if (dstk) {
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	}
	/* out: */
	*pprog = prog;
}