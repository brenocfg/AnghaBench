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
struct msm_mdss {int dummy; } ;
struct mdp5_mdss {scalar_t__ ahb_clk; scalar_t__ axi_clk; scalar_t__ vsync_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct mdp5_mdss* to_mdp5_mdss (struct msm_mdss*) ; 

__attribute__((used)) static int mdp5_mdss_disable(struct msm_mdss *mdss)
{
	struct mdp5_mdss *mdp5_mdss = to_mdp5_mdss(mdss);
	DBG("");

	if (mdp5_mdss->vsync_clk)
		clk_disable_unprepare(mdp5_mdss->vsync_clk);
	if (mdp5_mdss->axi_clk)
		clk_disable_unprepare(mdp5_mdss->axi_clk);
	clk_disable_unprepare(mdp5_mdss->ahb_clk);

	return 0;
}