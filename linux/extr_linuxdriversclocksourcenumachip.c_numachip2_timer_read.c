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
struct clocksource {int dummy; } ;
typedef  int /*<<< orphan*/  cycles_t ;

/* Variables and functions */
 int /*<<< orphan*/  NUMACHIP2_TIMER_NOW ; 
 int /*<<< orphan*/  numachip2_read64_lcsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static cycles_t numachip2_timer_read(struct clocksource *cs)
{
	return numachip2_read64_lcsr(NUMACHIP2_TIMER_NOW);
}