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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT2_off32 (int,int /*<<< orphan*/ ,scalar_t__ const) ; 
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT3_off32 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const) ; 
 int /*<<< orphan*/  const IA32_EAX ; 
 int /*<<< orphan*/  const IA32_EBP ; 
 int /*<<< orphan*/  STACK_VAR (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  add_1reg (int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  add_2reg (int,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void emit_ia32_mov_i(const u8 dst, const u32 val, bool dstk,
				   u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;

	if (dstk) {
		if (val == 0) {
			/* xor eax,eax */
			EMIT2(0x33, add_2reg(0xC0, IA32_EAX, IA32_EAX));
			/* mov dword ptr [ebp+off],eax */
			EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
			      STACK_VAR(dst));
		} else {
			EMIT3_off32(0xC7, add_1reg(0x40, IA32_EBP),
				    STACK_VAR(dst), val);
		}
	} else {
		if (val == 0)
			EMIT2(0x33, add_2reg(0xC0, dst, dst));
		else
			EMIT2_off32(0xC7, add_1reg(0xC0, dst),
				    val);
	}
	*pprog = prog;
}