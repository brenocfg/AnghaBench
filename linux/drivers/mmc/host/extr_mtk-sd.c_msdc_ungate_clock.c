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
struct msdc_host {scalar_t__ base; int /*<<< orphan*/  src_clk_cg; int /*<<< orphan*/  src_clk; int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  h_clk; } ;

/* Variables and functions */
 scalar_t__ MSDC_CFG ; 
 int MSDC_CFG_CKSTB ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void msdc_ungate_clock(struct msdc_host *host)
{
	clk_prepare_enable(host->h_clk);
	clk_prepare_enable(host->bus_clk);
	clk_prepare_enable(host->src_clk);
	clk_prepare_enable(host->src_clk_cg);
	while (!(readl(host->base + MSDC_CFG) & MSDC_CFG_CKSTB))
		cpu_relax();
}