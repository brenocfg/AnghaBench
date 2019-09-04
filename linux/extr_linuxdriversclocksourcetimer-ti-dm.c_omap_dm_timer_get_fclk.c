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
struct omap_dm_timer {struct clk* fclk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 

__attribute__((used)) static struct clk *omap_dm_timer_get_fclk(struct omap_dm_timer *timer)
{
	if (timer && !IS_ERR(timer->fclk))
		return timer->fclk;
	return NULL;
}