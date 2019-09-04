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
typedef  int /*<<< orphan*/  const u8 ;

/* Variables and functions */
#define  BPF_ADD 132 
#define  BPF_AND 131 
 int BPF_OP (int /*<<< orphan*/  const) ; 
#define  BPF_OR 130 
#define  BPF_SUB 129 
#define  BPF_XOR 128 
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const IA32_EAX ; 
 int /*<<< orphan*/  const IA32_EBP ; 
 int /*<<< orphan*/  const IA32_EDX ; 
 int /*<<< orphan*/  STACK_VAR (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  add_2reg (int,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void emit_ia32_alu_r(const bool is64, const bool hi, const u8 op,
				   const u8 dst, const u8 src, bool dstk,
				   bool sstk, u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;
	u8 sreg = sstk ? IA32_EAX : src;
	u8 dreg = dstk ? IA32_EDX : dst;

	if (sstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(src));

	if (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX), STACK_VAR(dst));

	switch (BPF_OP(op)) {
	/* dst = dst + src */
	case BPF_ADD:
		if (hi && is64)
			EMIT2(0x11, add_2reg(0xC0, dreg, sreg));
		else
			EMIT2(0x01, add_2reg(0xC0, dreg, sreg));
		break;
	/* dst = dst - src */
	case BPF_SUB:
		if (hi && is64)
			EMIT2(0x19, add_2reg(0xC0, dreg, sreg));
		else
			EMIT2(0x29, add_2reg(0xC0, dreg, sreg));
		break;
	/* dst = dst | src */
	case BPF_OR:
		EMIT2(0x09, add_2reg(0xC0, dreg, sreg));
		break;
	/* dst = dst & src */
	case BPF_AND:
		EMIT2(0x21, add_2reg(0xC0, dreg, sreg));
		break;
	/* dst = dst ^ src */
	case BPF_XOR:
		EMIT2(0x31, add_2reg(0xC0, dreg, sreg));
		break;
	}

	if (dstk)
		/* mov dword ptr [ebp+off],dreg */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg),
		      STACK_VAR(dst));
	*pprog = prog;
}