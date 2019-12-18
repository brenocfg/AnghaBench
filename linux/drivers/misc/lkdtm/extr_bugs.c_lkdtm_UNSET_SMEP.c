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

/* Variables and functions */
 int MOV_CR4_DEPTH ; 
 unsigned long X86_CR4_SMEP ; 
 unsigned long native_read_cr4 () ; 
 int /*<<< orphan*/  native_write_cr4 (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void lkdtm_UNSET_SMEP(void)
{
#ifdef CONFIG_X86_64
#define MOV_CR4_DEPTH	64
	void (*direct_write_cr4)(unsigned long val);
	unsigned char *insn;
	unsigned long cr4;
	int i;

	cr4 = native_read_cr4();

	if ((cr4 & X86_CR4_SMEP) != X86_CR4_SMEP) {
		pr_err("FAIL: SMEP not in use\n");
		return;
	}
	cr4 &= ~(X86_CR4_SMEP);

	pr_info("trying to clear SMEP normally\n");
	native_write_cr4(cr4);
	if (cr4 == native_read_cr4()) {
		pr_err("FAIL: pinning SMEP failed!\n");
		cr4 |= X86_CR4_SMEP;
		pr_info("restoring SMEP\n");
		native_write_cr4(cr4);
		return;
	}
	pr_info("ok: SMEP did not get cleared\n");

	/*
	 * To test the post-write pinning verification we need to call
	 * directly into the middle of native_write_cr4() where the
	 * cr4 write happens, skipping any pinning. This searches for
	 * the cr4 writing instruction.
	 */
	insn = (unsigned char *)native_write_cr4;
	for (i = 0; i < MOV_CR4_DEPTH; i++) {
		/* mov %rdi, %cr4 */
		if (insn[i] == 0x0f && insn[i+1] == 0x22 && insn[i+2] == 0xe7)
			break;
		/* mov %rdi,%rax; mov %rax, %cr4 */
		if (insn[i]   == 0x48 && insn[i+1] == 0x89 &&
		    insn[i+2] == 0xf8 && insn[i+3] == 0x0f &&
		    insn[i+4] == 0x22 && insn[i+5] == 0xe0)
			break;
	}
	if (i >= MOV_CR4_DEPTH) {
		pr_info("ok: cannot locate cr4 writing call gadget\n");
		return;
	}
	direct_write_cr4 = (void *)(insn + i);

	pr_info("trying to clear SMEP with call gadget\n");
	direct_write_cr4(cr4);
	if (native_read_cr4() & X86_CR4_SMEP) {
		pr_info("ok: SMEP removal was reverted\n");
	} else {
		pr_err("FAIL: cleared SMEP not detected!\n");
		cr4 |= X86_CR4_SMEP;
		pr_info("restoring SMEP\n");
		native_write_cr4(cr4);
	}
#else
	pr_err("FAIL: this test is x86_64-only\n");
#endif
}