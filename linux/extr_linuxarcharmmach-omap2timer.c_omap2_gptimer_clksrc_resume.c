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

/* Variables and functions */
 int OMAP_TIMER_CTRL_AR ; 
 int OMAP_TIMER_CTRL_ST ; 
 int /*<<< orphan*/  OMAP_TIMER_NONPOSTED ; 
 int /*<<< orphan*/  __omap_dm_timer_load_start (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clksrc ; 
 int /*<<< orphan*/  clocksource_gpt_hwmod ; 
 int /*<<< orphan*/  omap2_gptimer_clksrc_load ; 
 int /*<<< orphan*/  omap_hwmod_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_gptimer_clksrc_resume(struct clocksource *unused)
{
	omap_hwmod_enable(clocksource_gpt_hwmod);

	__omap_dm_timer_load_start(&clksrc,
				   OMAP_TIMER_CTRL_ST | OMAP_TIMER_CTRL_AR,
				   omap2_gptimer_clksrc_load,
				   OMAP_TIMER_NONPOSTED);
}