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
struct wuxga_nt_panel {int prepared; int /*<<< orphan*/  supply; int /*<<< orphan*/  earliest_wake; } ;
struct drm_panel {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ MIN_POFF_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 scalar_t__ ktime_ms_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct wuxga_nt_panel* to_wuxga_nt_panel (struct drm_panel*) ; 
 int wuxga_nt_panel_on (struct wuxga_nt_panel*) ; 

__attribute__((used)) static int wuxga_nt_panel_prepare(struct drm_panel *panel)
{
	struct wuxga_nt_panel *wuxga_nt = to_wuxga_nt_panel(panel);
	int ret;
	s64 enablewait;

	if (wuxga_nt->prepared)
		return 0;

	/*
	 * If the user re-enabled the panel before the required off-time then
	 * we need to wait the remaining period before re-enabling regulator
	 */
	enablewait = ktime_ms_delta(wuxga_nt->earliest_wake, ktime_get_real());

	/* Sanity check, this should never happen */
	if (enablewait > MIN_POFF_MS)
		enablewait = MIN_POFF_MS;

	if (enablewait > 0)
		msleep(enablewait);

	ret = regulator_enable(wuxga_nt->supply);
	if (ret < 0)
		return ret;

	/*
	 * A minimum delay of 250ms is required after power-up until commands
	 * can be sent
	 */
	msleep(250);

	ret = wuxga_nt_panel_on(wuxga_nt);
	if (ret < 0) {
		dev_err(panel->dev, "failed to set panel on: %d\n", ret);
		goto poweroff;
	}

	wuxga_nt->prepared = true;

	return 0;

poweroff:
	regulator_disable(wuxga_nt->supply);

	return ret;
}