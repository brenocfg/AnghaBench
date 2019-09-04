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
 int /*<<< orphan*/  register_undef_hook (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprobes_arm_break_hook ; 
 int /*<<< orphan*/  uprobes_arm_ss_hook ; 

__attribute__((used)) static int arch_uprobes_init(void)
{
	register_undef_hook(&uprobes_arm_break_hook);
	register_undef_hook(&uprobes_arm_ss_hook);

	return 0;
}