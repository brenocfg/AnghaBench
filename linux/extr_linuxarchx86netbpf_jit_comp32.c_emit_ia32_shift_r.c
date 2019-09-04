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
typedef  scalar_t__ u8 ;

/* Variables and functions */
#define  BPF_ARSH 130 
#define  BPF_LSH 129 
#define  BPF_RSH 128 
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ const IA32_EAX ; 
 scalar_t__ const IA32_EBP ; 
 scalar_t__ const IA32_ECX ; 
 int /*<<< orphan*/  STACK_VAR (scalar_t__ const) ; 
 int /*<<< orphan*/  add_1reg (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  add_2reg (int,scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static inline void emit_ia32_shift_r(const u8 op, const u8 dst, const u8 src,
				     bool dstk, bool sstk, u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;
	u8 dreg = dstk ? IA32_EAX : dst;
	u8 b2;

	if (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(dst));

	if (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX), STACK_VAR(src));
	else if (src != IA32_ECX)
		/* mov ecx,src */
		EMIT2(0x8B, add_2reg(0xC0, src, IA32_ECX));

	switch (op) {
	case BPF_LSH:
		b2 = 0xE0; break;
	case BPF_RSH:
		b2 = 0xE8; break;
	case BPF_ARSH:
		b2 = 0xF8; break;
	default:
		return;
	}
	EMIT2(0xD3, add_1reg(b2, dreg));

	if (dstk)
		/* mov dword ptr [ebp+off],dreg */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg), STACK_VAR(dst));
	*pprog = prog;
}