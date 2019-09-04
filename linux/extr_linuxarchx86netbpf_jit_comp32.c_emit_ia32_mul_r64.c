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
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IA32_EAX ; 
 int /*<<< orphan*/  IA32_EBP ; 
 int /*<<< orphan*/  IA32_ECX ; 
 int /*<<< orphan*/  IA32_EDX ; 
 int /*<<< orphan*/  STACK_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_1reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_2reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 
 int /*<<< orphan*/  src_hi ; 
 int /*<<< orphan*/  src_lo ; 

__attribute__((used)) static inline void emit_ia32_mul_r64(const u8 dst[], const u8 src[], bool dstk,
				     bool sstk, u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;

	if (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_hi));
	else
		/* mov eax,dst_hi */
		EMIT2(0x8B, add_2reg(0xC0, dst_hi, IA32_EAX));

	if (sstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(src_lo));
	else
		/* mul src_lo */
		EMIT2(0xF7, add_1reg(0xE0, src_lo));

	/* mov ecx,eax */
	EMIT2(0x89, add_2reg(0xC0, IA32_ECX, IA32_EAX));

	if (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
	else
		/* mov eax,dst_lo */
		EMIT2(0x8B, add_2reg(0xC0, dst_lo, IA32_EAX));

	if (sstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(src_hi));
	else
		/* mul src_hi */
		EMIT2(0xF7, add_1reg(0xE0, src_hi));

	/* add eax,eax */
	EMIT2(0x01, add_2reg(0xC0, IA32_ECX, IA32_EAX));

	if (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
	else
		/* mov eax,dst_lo */
		EMIT2(0x8B, add_2reg(0xC0, dst_lo, IA32_EAX));

	if (sstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(src_lo));
	else
		/* mul src_lo */
		EMIT2(0xF7, add_1reg(0xE0, src_lo));

	/* add ecx,edx */
	EMIT2(0x01, add_2reg(0xC0, IA32_ECX, IA32_EDX));

	if (dstk) {
		/* mov dword ptr [ebp+off],eax */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],ecx */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(dst_hi));
	} else {
		/* mov dst_lo,eax */
		EMIT2(0x89, add_2reg(0xC0, dst_lo, IA32_EAX));
		/* mov dst_hi,ecx */
		EMIT2(0x89, add_2reg(0xC0, dst_hi, IA32_ECX));
	}

	*pprog = prog;
}