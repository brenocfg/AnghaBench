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
 scalar_t__ exception_handler_hook ; 

__attribute__((used)) static inline void copy_exception_handler(unsigned int addr)
{
	unsigned int start = (unsigned int) exception_handler_hook;
	volatile unsigned int tmp = 0;

	if (start == addr) {
		/* The CPU exception address already points to the handler. */
		return;
	}

	__asm__ __volatile__ (
		"ldw	%2,0(%0)\n"
		"stw	%2,0(%1)\n"
		"ldw	%2,4(%0)\n"
		"stw	%2,4(%1)\n"
		"ldw	%2,8(%0)\n"
		"stw	%2,8(%1)\n"
		"flushd	0(%1)\n"
		"flushd	4(%1)\n"
		"flushd	8(%1)\n"
		"flushi %1\n"
		"addi	%1,%1,4\n"
		"flushi %1\n"
		"addi	%1,%1,4\n"
		"flushi %1\n"
		"flushp\n"
		: /* no output registers */
		: "r" (start), "r" (addr), "r" (tmp)
		: "memory"
	);
}