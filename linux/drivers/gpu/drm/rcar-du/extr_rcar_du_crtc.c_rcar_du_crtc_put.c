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
 int /*<<< orphan*/  rcar_du_group_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_du_crtc_put(struct rcar_du_crtc *rcrtc)
{
	rcar_du_group_put(rcrtc->group);

	clk_disable_unprepare(rcrtc->extclock);
	clk_disable_unprepare(rcrtc->clock);

	rcrtc->initialized = false;
}