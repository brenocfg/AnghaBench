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
 unsigned long ctx_map ; 
 int ffs (unsigned long) ; 
 int /*<<< orphan*/  restore_hw_context (int) ; 

void omap_vrfb_restore_context(void)
{
	int i;
	unsigned long map = ctx_map;

	for (i = ffs(map); i; i = ffs(map)) {
		/* i=1..32 */
		i--;
		map &= ~(1 << i);
		restore_hw_context(i);
	}
}