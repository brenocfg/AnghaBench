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
struct timespec64 {int dummy; } ;
typedef  scalar_t__ cycles_t ;

/* Variables and functions */
 unsigned long long clocksource_cyc2ns (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cycles ; 
 int /*<<< orphan*/  persistent_mult ; 
 int /*<<< orphan*/  persistent_shift ; 
 struct timespec64 persistent_ts ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 scalar_t__ sync32k_cnt_reg ; 
 int /*<<< orphan*/  timespec64_add_ns (struct timespec64*,unsigned long long) ; 

__attribute__((used)) static void omap_read_persistent_clock64(struct timespec64 *ts)
{
	unsigned long long nsecs;
	cycles_t last_cycles;

	last_cycles = cycles;
	cycles = sync32k_cnt_reg ? readl_relaxed(sync32k_cnt_reg) : 0;

	nsecs = clocksource_cyc2ns(cycles - last_cycles,
					persistent_mult, persistent_shift);

	timespec64_add_ns(&persistent_ts, nsecs);

	*ts = persistent_ts;
}