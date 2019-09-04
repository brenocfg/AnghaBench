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
struct patch {int /*<<< orphan*/  insn; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __patch_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __kprobes_remove_breakpoint(void *data)
{
	struct patch *p = data;
	__patch_text(p->addr, p->insn);
	return 0;
}