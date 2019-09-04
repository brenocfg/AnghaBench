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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT2 (int,int const) ; 
 int /*<<< orphan*/  EMIT3 (int,int,int const) ; 
 int /*<<< orphan*/  IA32_EAX ; 
 int /*<<< orphan*/  IA32_EBP ; 
 int /*<<< orphan*/  IA32_EBX ; 
 int /*<<< orphan*/  IA32_ECX ; 
 int /*<<< orphan*/  IA32_EDX ; 
 int STACK_VAR (int /*<<< orphan*/ ) ; 
 int add_1reg (int,int /*<<< orphan*/ ) ; 
 int add_2reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 

__attribute__((used)) static inline void emit_ia32_rsh_i64(const u8 dst[], const u32 val,
				     bool dstk, u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	}

	/* Do RSH operation */
	if (val < 32) {
		/* shr dreg_lo,imm8 */
		EMIT3(0xC1, add_1reg(0xE8, dreg_lo), val);
		/* mov ebx,dreg_hi */
		EMIT2(0x8B, add_2reg(0xC0, dreg_hi, IA32_EBX));
		/* shr dreg_hi,imm8 */
		EMIT3(0xC1, add_1reg(0xE8, dreg_hi), val);

		/* IA32_ECX = 32 - val */
		/* mov ecx,val */
		EMIT2(0xB1, val);
		/* movzx ecx,ecx */
		EMIT3(0x0F, 0xB6, add_2reg(0xC0, IA32_ECX, IA32_ECX));
		/* neg ecx */
		EMIT2(0xF7, add_1reg(0xD8, IA32_ECX));
		/* add ecx,32 */
		EMIT3(0x83, add_1reg(0xC0, IA32_ECX), 32);

		/* shl ebx,cl */
		EMIT2(0xD3, add_1reg(0xE0, IA32_EBX));
		/* or dreg_lo,ebx */
		EMIT2(0x09, add_2reg(0xC0, dreg_lo, IA32_EBX));
	} else if (val >= 32 && val < 64) {
		u32 value = val - 32;

		/* shr dreg_hi,imm8 */
		EMIT3(0xC1, add_1reg(0xE8, dreg_hi), value);
		/* mov dreg_lo,dreg_hi */
		EMIT2(0x89, add_2reg(0xC0, dreg_lo, dreg_hi));
		/* xor dreg_hi,dreg_hi */
		EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
	} else {
		/* xor dreg_lo,dreg_lo */
		EMIT2(0x33, add_2reg(0xC0, dreg_lo, dreg_lo));
		/* xor dreg_hi,dreg_hi */
		EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
	}

	if (dstk) {
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	}
	*pprog = prog;
}