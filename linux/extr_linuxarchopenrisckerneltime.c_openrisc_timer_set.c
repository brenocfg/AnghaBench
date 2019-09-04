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
 int /*<<< orphan*/  SPR_TTCR ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 

inline void openrisc_timer_set(unsigned long count)
{
	mtspr(SPR_TTCR, count);
}