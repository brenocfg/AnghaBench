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
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */

__attribute__((used)) static void synthesize_set_arg1(kprobe_opcode_t *addr, unsigned long val)
{
#ifdef CONFIG_X86_64
	*addr++ = 0x48;
	*addr++ = 0xbf;
#else
	*addr++ = 0xb8;
#endif
	*(unsigned long *)addr = val;
}