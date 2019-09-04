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
 int TEST_FLAG_FULL_ITBLOCK ; 
 int TEST_FLAG_NO_ITBLOCK ; 
 int current_instruction ; 
 int is_last_scenario ; 
 int kprobe_test_cc_position ; 
 int kprobe_test_flags ; 
 int probe_should_run ; 
 int /*<<< orphan*/  test_case_is_thumb ; 
 scalar_t__ test_check_cc (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long test_context_cpsr(int scenario)
{
	unsigned long cpsr;

	probe_should_run = 1;

	/* Default case is that we cycle through 16 combinations of flags */
	cpsr  = (scenario & 0xf) << 28; /* N,Z,C,V flags */
	cpsr |= (scenario & 0xf) << 16; /* GE flags */
	cpsr |= (scenario & 0x1) << 27; /* Toggle Q flag */

	if (!test_case_is_thumb) {
		/* Testing ARM code */
		int cc = current_instruction >> 28;

		probe_should_run = test_check_cc(cc, cpsr) != 0;
		if (scenario == 15)
			is_last_scenario = true;

	} else if (kprobe_test_flags & TEST_FLAG_NO_ITBLOCK) {
		/* Testing Thumb code without setting ITSTATE */
		if (kprobe_test_cc_position) {
			int cc = (current_instruction >> kprobe_test_cc_position) & 0xf;
			probe_should_run = test_check_cc(cc, cpsr) != 0;
		}

		if (scenario == 15)
			is_last_scenario = true;

	} else if (kprobe_test_flags & TEST_FLAG_FULL_ITBLOCK) {
		/* Testing Thumb code with all combinations of ITSTATE */
		unsigned x = (scenario >> 4);
		unsigned cond_base = x % 7; /* ITSTATE<7:5> */
		unsigned mask = x / 7 + 2;  /* ITSTATE<4:0>, bits reversed */

		if (mask > 0x1f) {
			/* Finish by testing state from instruction 'itt al' */
			cond_base = 7;
			mask = 0x4;
			if ((scenario & 0xf) == 0xf)
				is_last_scenario = true;
		}

		cpsr |= cond_base << 13;	/* ITSTATE<7:5> */
		cpsr |= (mask & 0x1) << 12;	/* ITSTATE<4> */
		cpsr |= (mask & 0x2) << 10;	/* ITSTATE<3> */
		cpsr |= (mask & 0x4) << 8;	/* ITSTATE<2> */
		cpsr |= (mask & 0x8) << 23;	/* ITSTATE<1> */
		cpsr |= (mask & 0x10) << 21;	/* ITSTATE<0> */

		probe_should_run = test_check_cc((cpsr >> 12) & 0xf, cpsr) != 0;

	} else {
		/* Testing Thumb code with several combinations of ITSTATE */
		switch (scenario) {
		case 16: /* Clear NZCV flags and 'it eq' state (false as Z=0) */
			cpsr = 0x00000800;
			probe_should_run = 0;
			break;
		case 17: /* Set NZCV flags and 'it vc' state (false as V=1) */
			cpsr = 0xf0007800;
			probe_should_run = 0;
			break;
		case 18: /* Clear NZCV flags and 'it ls' state (true as C=0) */
			cpsr = 0x00009800;
			break;
		case 19: /* Set NZCV flags and 'it cs' state (true as C=1) */
			cpsr = 0xf0002800;
			is_last_scenario = true;
			break;
		}
	}

	return cpsr;
}