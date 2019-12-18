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
struct mtk_hdmi_phy {TYPE_1__* conf; } ;
struct clk_init_data {int /*<<< orphan*/  ops; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  hdmi_phy_clk_ops; int /*<<< orphan*/  flags; } ;

/* Variables and functions */

__attribute__((used)) static void mtk_hdmi_phy_clk_get_data(struct mtk_hdmi_phy *hdmi_phy,
				      struct clk_init_data *clk_init)
{
	clk_init->flags = hdmi_phy->conf->flags;
	clk_init->ops = hdmi_phy->conf->hdmi_phy_clk_ops;
}