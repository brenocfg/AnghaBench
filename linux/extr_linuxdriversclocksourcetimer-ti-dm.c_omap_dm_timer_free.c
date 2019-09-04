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
struct omap_dm_timer {scalar_t__ reserved; int /*<<< orphan*/  fclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int omap_dm_timer_free(struct omap_dm_timer *timer)
{
	if (unlikely(!timer))
		return -EINVAL;

	clk_put(timer->fclk);

	WARN_ON(!timer->reserved);
	timer->reserved = 0;
	return 0;
}