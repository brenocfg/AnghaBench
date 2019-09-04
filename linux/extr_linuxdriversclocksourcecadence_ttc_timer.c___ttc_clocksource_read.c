#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ttc_timer {scalar_t__ base_addr; } ;
struct clocksource {int dummy; } ;
struct TYPE_2__ {struct ttc_timer ttc; } ;

/* Variables and functions */
 scalar_t__ TTC_COUNT_VAL_OFFSET ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 TYPE_1__* to_ttc_timer_clksrc (struct clocksource*) ; 

__attribute__((used)) static u64 __ttc_clocksource_read(struct clocksource *cs)
{
	struct ttc_timer *timer = &to_ttc_timer_clksrc(cs)->ttc;

	return (u64)readl_relaxed(timer->base_addr +
				TTC_COUNT_VAL_OFFSET);
}