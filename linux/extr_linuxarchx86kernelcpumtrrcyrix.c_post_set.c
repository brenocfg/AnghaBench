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
 int /*<<< orphan*/  CX86_CCR3 ; 
 int X86_CR0_CD ; 
 int /*<<< orphan*/  X86_FEATURE_PGE ; 
 int /*<<< orphan*/  __write_cr4 (int /*<<< orphan*/ ) ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccr3 ; 
 int /*<<< orphan*/  cr4 ; 
 int read_cr0 () ; 
 int /*<<< orphan*/  setCx86 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  write_cr0 (int) ; 

__attribute__((used)) static void post_set(void)
{
	/* Flush caches and TLBs */
	wbinvd();

	/* Cyrix ARRs - everything else was excluded at the top */
	setCx86(CX86_CCR3, ccr3);

	/* Enable caches */
	write_cr0(read_cr0() & ~X86_CR0_CD);

	/* Restore value of CR4 */
	if (boot_cpu_has(X86_FEATURE_PGE))
		__write_cr4(cr4);
}