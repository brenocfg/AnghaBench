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
 int /*<<< orphan*/  PNV_THREAD_NAP ; 
 int /*<<< orphan*/  power7_idle_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powersave_nap ; 

void power7_idle(void)
{
	if (!powersave_nap)
		return;

	power7_idle_type(PNV_THREAD_NAP);
}