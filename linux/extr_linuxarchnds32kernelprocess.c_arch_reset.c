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
 int /*<<< orphan*/  cpu_reset (int /*<<< orphan*/ ) ; 

extern inline void arch_reset(char mode)
{
	if (mode == 's') {
		/* Use cpu handler, jump to 0 */
		cpu_reset(0);
	}
}