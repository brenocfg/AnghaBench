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
typedef  int /*<<< orphan*/  uprobe_opcode_t ;

/* Variables and functions */
 int is_trap (int /*<<< orphan*/ ) ; 

bool is_trap_insn(uprobe_opcode_t *insn)
{
	return (is_trap(*insn));
}