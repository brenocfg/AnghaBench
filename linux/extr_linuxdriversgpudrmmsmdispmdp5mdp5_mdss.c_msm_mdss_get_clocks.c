#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct mdp5_mdss {int /*<<< orphan*/ * vsync_clk; int /*<<< orphan*/ * axi_clk; int /*<<< orphan*/ * ahb_clk; TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 void* msm_clk_get (struct platform_device*,char*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm_mdss_get_clocks(struct mdp5_mdss *mdp5_mdss)
{
	struct platform_device *pdev =
			to_platform_device(mdp5_mdss->base.dev->dev);

	mdp5_mdss->ahb_clk = msm_clk_get(pdev, "iface");
	if (IS_ERR(mdp5_mdss->ahb_clk))
		mdp5_mdss->ahb_clk = NULL;

	mdp5_mdss->axi_clk = msm_clk_get(pdev, "bus");
	if (IS_ERR(mdp5_mdss->axi_clk))
		mdp5_mdss->axi_clk = NULL;

	mdp5_mdss->vsync_clk = msm_clk_get(pdev, "vsync");
	if (IS_ERR(mdp5_mdss->vsync_clk))
		mdp5_mdss->vsync_clk = NULL;

	return 0;
}