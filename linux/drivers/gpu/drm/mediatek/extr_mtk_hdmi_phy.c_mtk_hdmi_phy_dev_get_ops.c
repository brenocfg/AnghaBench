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
struct phy_ops {int dummy; } ;
struct mtk_hdmi_phy {int /*<<< orphan*/  dev; TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ hdmi_phy_disable_tmds; scalar_t__ hdmi_phy_enable_tmds; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct phy_ops const mtk_hdmi_phy_dev_ops ; 

__attribute__((used)) static const struct phy_ops *
mtk_hdmi_phy_dev_get_ops(const struct mtk_hdmi_phy *hdmi_phy)
{
	if (hdmi_phy && hdmi_phy->conf &&
	    hdmi_phy->conf->hdmi_phy_enable_tmds &&
	    hdmi_phy->conf->hdmi_phy_disable_tmds)
		return &mtk_hdmi_phy_dev_ops;

	dev_err(hdmi_phy->dev, "Failed to get dev ops of phy\n");
		return NULL;
}