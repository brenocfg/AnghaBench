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
struct msdc_host {int /*<<< orphan*/  h_clk; int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  src_clk; int /*<<< orphan*/  src_clk_cg; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msdc_gate_clock(struct msdc_host *host)
{
	clk_disable_unprepare(host->src_clk_cg);
	clk_disable_unprepare(host->src_clk);
	clk_disable_unprepare(host->bus_clk);
	clk_disable_unprepare(host->h_clk);
}