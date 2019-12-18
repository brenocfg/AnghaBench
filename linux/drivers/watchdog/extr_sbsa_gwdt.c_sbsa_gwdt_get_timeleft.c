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
typedef  unsigned int u64 ;
struct watchdog_device {int dummy; } ;
struct sbsa_gwdt {int /*<<< orphan*/  clk; scalar_t__ control_base; } ;

/* Variables and functions */
 scalar_t__ SBSA_GWDT_WCS ; 
 unsigned int SBSA_GWDT_WCS_WS0 ; 
 scalar_t__ SBSA_GWDT_WCV ; 
 scalar_t__ SBSA_GWDT_WOR ; 
 int /*<<< orphan*/  action ; 
 scalar_t__ arch_timer_read_counter () ; 
 int /*<<< orphan*/  do_div (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ lo_hi_readq (scalar_t__) ; 
 unsigned int readl (scalar_t__) ; 
 struct sbsa_gwdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int sbsa_gwdt_get_timeleft(struct watchdog_device *wdd)
{
	struct sbsa_gwdt *gwdt = watchdog_get_drvdata(wdd);
	u64 timeleft = 0;

	/*
	 * In the single stage mode, if WS0 is deasserted
	 * (watchdog is in the first stage),
	 * timeleft = WOR + (WCV - system counter)
	 */
	if (!action &&
	    !(readl(gwdt->control_base + SBSA_GWDT_WCS) & SBSA_GWDT_WCS_WS0))
		timeleft += readl(gwdt->control_base + SBSA_GWDT_WOR);

	timeleft += lo_hi_readq(gwdt->control_base + SBSA_GWDT_WCV) -
		    arch_timer_read_counter();

	do_div(timeleft, gwdt->clk);

	return timeleft;
}