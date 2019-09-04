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
typedef  int u8 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  BPF_ADD 133 
#define  BPF_AND 132 
#define  BPF_NEG 131 
#define  BPF_OR 130 
#define  BPF_SUB 129 
#define  BPF_XOR 128 
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT2_off32 (int,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int const IA32_EAX ; 
 int IA32_EBP ; 
 int IA32_EDX ; 
 int /*<<< orphan*/  const STACK_VAR (int const) ; 
 int /*<<< orphan*/  add_1reg (int,int) ; 
 int /*<<< orphan*/  add_2reg (int,int,int const) ; 
 scalar_t__ is_imm8 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void emit_ia32_alu_i(const bool is64, const bool hi, const u8 op,
				   const u8 dst, const s32 val, bool dstk,
				   u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;
	u8 dreg = dstk ? IA32_EAX : dst;
	u8 sreg = IA32_EDX;

	if (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(dst));

	if (!is_imm8(val))
		/* mov edx,imm32*/
		EMIT2_off32(0xC7, add_1reg(0xC0, IA32_EDX), val);

	switch (op) {
	/* dst = dst + val */
	case BPF_ADD:
		if (hi && is64) {
			if (is_imm8(val))
				EMIT3(0x83, add_1reg(0xD0, dreg), val);
			else
				EMIT2(0x11, add_2reg(0xC0, dreg, sreg));
		} else {
			if (is_imm8(val))
				EMIT3(0x83, add_1reg(0xC0, dreg), val);
			else
				EMIT2(0x01, add_2reg(0xC0, dreg, sreg));
		}
		break;
	/* dst = dst - val */
	case BPF_SUB:
		if (hi && is64) {
			if (is_imm8(val))
				EMIT3(0x83, add_1reg(0xD8, dreg), val);
			else
				EMIT2(0x19, add_2reg(0xC0, dreg, sreg));
		} else {
			if (is_imm8(val))
				EMIT3(0x83, add_1reg(0xE8, dreg), val);
			else
				EMIT2(0x29, add_2reg(0xC0, dreg, sreg));
		}
		break;
	/* dst = dst | val */
	case BPF_OR:
		if (is_imm8(val))
			EMIT3(0x83, add_1reg(0xC8, dreg), val);
		else
			EMIT2(0x09, add_2reg(0xC0, dreg, sreg));
		break;
	/* dst = dst & val */
	case BPF_AND:
		if (is_imm8(val))
			EMIT3(0x83, add_1reg(0xE0, dreg), val);
		else
			EMIT2(0x21, add_2reg(0xC0, dreg, sreg));
		break;
	/* dst = dst ^ val */
	case BPF_XOR:
		if (is_imm8(val))
			EMIT3(0x83, add_1reg(0xF0, dreg), val);
		else
			EMIT2(0x31, add_2reg(0xC0, dreg, sreg));
		break;
	case BPF_NEG:
		EMIT2(0xF7, add_1reg(0xD8, dreg));
		break;
	}

	if (dstk)
		/* mov dword ptr [ebp+off],dreg */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg),
		      STACK_VAR(dst));
	*pprog = prog;
}