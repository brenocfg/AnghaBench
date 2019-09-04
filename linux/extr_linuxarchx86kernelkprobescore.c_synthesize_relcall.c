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
 int /*<<< orphan*/  RELATIVECALL_OPCODE ; 
 int /*<<< orphan*/  __synthesize_relative_insn (void*,void*,void*,int /*<<< orphan*/ ) ; 

void synthesize_relcall(void *dest, void *from, void *to)
{
	__synthesize_relative_insn(dest, from, to, RELATIVECALL_OPCODE);
}