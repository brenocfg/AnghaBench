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
 int /*<<< orphan*/  _PAGE_ACCESSED_SHIFT ; 
 int /*<<< orphan*/  _PAGE_DIRTY_SHIFT ; 
 int /*<<< orphan*/  _PAGE_GLOBAL_SHIFT ; 
 int /*<<< orphan*/  _PAGE_MODIFIED_SHIFT ; 
 int /*<<< orphan*/  _PAGE_NO_READ_SHIFT ; 
 int /*<<< orphan*/  _PAGE_PRESENT_SHIFT ; 
 int /*<<< orphan*/  _PAGE_VALID_SHIFT ; 
 int /*<<< orphan*/  _PAGE_WRITE_SHIFT ; 
 int /*<<< orphan*/  _PFN_SHIFT ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void output_pgtable_bits_defines(void)
{
#define pr_define(fmt, ...)					\
	pr_debug("#define " fmt, ##__VA_ARGS__)

	pr_debug("#include <asm/asm.h>\n");
	pr_debug("#include <asm/regdef.h>\n");
	pr_debug("\n");

	pr_define("_PAGE_PRESENT_SHIFT %d\n", _PAGE_PRESENT_SHIFT);
	pr_define("_PAGE_NO_READ_SHIFT %d\n", _PAGE_NO_READ_SHIFT);
	pr_define("_PAGE_WRITE_SHIFT %d\n", _PAGE_WRITE_SHIFT);
	pr_define("_PAGE_ACCESSED_SHIFT %d\n", _PAGE_ACCESSED_SHIFT);
	pr_define("_PAGE_MODIFIED_SHIFT %d\n", _PAGE_MODIFIED_SHIFT);
#ifdef CONFIG_MIPS_HUGE_TLB_SUPPORT
	pr_define("_PAGE_HUGE_SHIFT %d\n", _PAGE_HUGE_SHIFT);
#endif
#ifdef _PAGE_NO_EXEC_SHIFT
	if (cpu_has_rixi)
		pr_define("_PAGE_NO_EXEC_SHIFT %d\n", _PAGE_NO_EXEC_SHIFT);
#endif
	pr_define("_PAGE_GLOBAL_SHIFT %d\n", _PAGE_GLOBAL_SHIFT);
	pr_define("_PAGE_VALID_SHIFT %d\n", _PAGE_VALID_SHIFT);
	pr_define("_PAGE_DIRTY_SHIFT %d\n", _PAGE_DIRTY_SHIFT);
	pr_define("_PFN_SHIFT %d\n", _PFN_SHIFT);
	pr_debug("\n");
}