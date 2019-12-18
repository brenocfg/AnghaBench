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
struct rcar_du_crtc {int initialized; int /*<<< orphan*/  clock; int /*<<< orphan*/  extclock; int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_crtc_setup (struct rcar_du_crtc*) ; 
 int rcar_du_group_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_du_crtc_get(struct rcar_du_crtc *rcrtc)
{
	int ret;

	/*
	 * Guard against double-get, as the function is called from both the
	 * .atomic_enable() and .atomic_begin() handlers.
	 */
	if (rcrtc->initialized)
		return 0;

	ret = clk_prepare_enable(rcrtc->clock);
	if (ret < 0)
		return ret;

	ret = clk_prepare_enable(rcrtc->extclock);
	if (ret < 0)
		goto error_clock;

	ret = rcar_du_group_get(rcrtc->group);
	if (ret < 0)
		goto error_group;

	rcar_du_crtc_setup(rcrtc);
	rcrtc->initialized = true;

	return 0;

error_group:
	clk_disable_unprepare(rcrtc->extclock);
error_clock:
	clk_disable_unprepare(rcrtc->clock);
	return ret;
}