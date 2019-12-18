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
struct xsdfec_clks {int /*<<< orphan*/  axi_clk; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  din_clk; int /*<<< orphan*/  din_words_clk; int /*<<< orphan*/  dout_clk; int /*<<< orphan*/  dout_words_clk; int /*<<< orphan*/  ctrl_clk; int /*<<< orphan*/  status_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xsdfec_disable_all_clks(struct xsdfec_clks *clks)
{
	clk_disable_unprepare(clks->status_clk);
	clk_disable_unprepare(clks->ctrl_clk);
	clk_disable_unprepare(clks->dout_words_clk);
	clk_disable_unprepare(clks->dout_clk);
	clk_disable_unprepare(clks->din_words_clk);
	clk_disable_unprepare(clks->din_clk);
	clk_disable_unprepare(clks->core_clk);
	clk_disable_unprepare(clks->axi_clk);
}