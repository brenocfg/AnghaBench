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
struct omap_dm_timer {int capability; TYPE_1__* pdev; int /*<<< orphan*/  fclk; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int OMAP_TIMER_NEEDS_RESET ; 
 int /*<<< orphan*/  OMAP_TIMER_SRC_32_KHZ ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __omap_dm_timer_enable_posted (struct omap_dm_timer*) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  omap_dm_timer_disable (struct omap_dm_timer*) ; 
 int /*<<< orphan*/  omap_dm_timer_enable (struct omap_dm_timer*) ; 
 int omap_dm_timer_of_set_source (struct omap_dm_timer*) ; 
 int omap_dm_timer_reset (struct omap_dm_timer*) ; 
 int omap_dm_timer_set_source (struct omap_dm_timer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_dm_timer_prepare(struct omap_dm_timer *timer)
{
	int rc;

	/*
	 * FIXME: OMAP1 devices do not use the clock framework for dmtimers so
	 * do not call clk_get() for these devices.
	 */
	if (!(timer->capability & OMAP_TIMER_NEEDS_RESET)) {
		timer->fclk = clk_get(&timer->pdev->dev, "fck");
		if (WARN_ON_ONCE(IS_ERR(timer->fclk))) {
			dev_err(&timer->pdev->dev, ": No fclk handle.\n");
			return -EINVAL;
		}
	}

	omap_dm_timer_enable(timer);

	if (timer->capability & OMAP_TIMER_NEEDS_RESET) {
		rc = omap_dm_timer_reset(timer);
		if (rc) {
			omap_dm_timer_disable(timer);
			return rc;
		}
	}

	__omap_dm_timer_enable_posted(timer);
	omap_dm_timer_disable(timer);

	rc = omap_dm_timer_of_set_source(timer);
	if (rc == -ENODEV)
		return omap_dm_timer_set_source(timer, OMAP_TIMER_SRC_32_KHZ);

	return rc;
}