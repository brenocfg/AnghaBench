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
struct csi_state {int /*<<< orphan*/  clks; int /*<<< orphan*/  num_clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mipi_csis_clk_disable(struct csi_state *state)
{
	clk_bulk_disable_unprepare(state->num_clks, state->clks);
}