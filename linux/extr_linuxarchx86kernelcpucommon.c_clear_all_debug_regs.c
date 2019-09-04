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
 int /*<<< orphan*/  set_debugreg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_all_debug_regs(void)
{
	int i;

	for (i = 0; i < 8; i++) {
		/* Ignore db4, db5 */
		if ((i == 4) || (i == 5))
			continue;

		set_debugreg(0, i);
	}
}