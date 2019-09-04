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
struct branch {int opcode; unsigned long delta; } ;

/* Variables and functions */

unsigned paravirt_patch_jmp(void *insnbuf, const void *target,
			    unsigned long addr, unsigned len)
{
	struct branch *b = insnbuf;
	unsigned long delta = (unsigned long)target - (addr+5);

	if (len < 5) {
#ifdef CONFIG_RETPOLINE
		WARN_ONCE(1, "Failing to patch indirect JMP in %ps\n", (void *)addr);
#endif
		return len;	/* call too long for patch site */
	}

	b->opcode = 0xe9;	/* jmp */
	b->delta = delta;

	return 5;
}