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
struct arch_elf_state {int overall_fp_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CONFIG_MIPS_O32_FP64_SUPPORT ; 
#define  FP_FR0 130 
#define  FP_FR1 129 
#define  FP_FRE 128 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_thread_fp_mode (int,int) ; 

void mips_set_personality_fp(struct arch_elf_state *state)
{
	/*
	 * This function is only ever called for O32 ELFs so we should
	 * not be worried about N32/N64 binaries.
	 */

	if (!IS_ENABLED(CONFIG_MIPS_O32_FP64_SUPPORT))
		return;

	switch (state->overall_fp_mode) {
	case FP_FRE:
		set_thread_fp_mode(1, 0);
		break;
	case FP_FR0:
		set_thread_fp_mode(0, 1);
		break;
	case FP_FR1:
		set_thread_fp_mode(0, 0);
		break;
	default:
		BUG();
	}
}