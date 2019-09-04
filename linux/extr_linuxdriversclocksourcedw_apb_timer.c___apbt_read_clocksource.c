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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct dw_apb_clocksource {int /*<<< orphan*/  timer; } ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APBTMR_N_CURRENT_VALUE ; 
 int /*<<< orphan*/  apbt_readl_relaxed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dw_apb_clocksource* clocksource_to_dw_apb_clocksource (struct clocksource*) ; 

__attribute__((used)) static u64 __apbt_read_clocksource(struct clocksource *cs)
{
	u32 current_count;
	struct dw_apb_clocksource *dw_cs =
		clocksource_to_dw_apb_clocksource(cs);

	current_count = apbt_readl_relaxed(&dw_cs->timer,
					APBTMR_N_CURRENT_VALUE);

	return (u64)~current_count;
}