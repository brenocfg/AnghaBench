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
 int /*<<< orphan*/  _clkdm_restore_context ; 
 int /*<<< orphan*/  clkdm_for_each (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void clkdm_restore_context(void)
{
	clkdm_for_each(_clkdm_restore_context, NULL);
}