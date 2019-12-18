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
struct phy {int dummy; } ;
struct inno_hdmi_phy {int /*<<< orphan*/  dev; int /*<<< orphan*/  phyclk; TYPE_2__* plat_data; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* power_off ) (struct inno_hdmi_phy*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct inno_hdmi_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  stub1 (struct inno_hdmi_phy*) ; 

__attribute__((used)) static int inno_hdmi_phy_power_off(struct phy *phy)
{
	struct inno_hdmi_phy *inno = phy_get_drvdata(phy);

	if (!inno->plat_data->ops->power_off)
		return -EINVAL;

	inno->plat_data->ops->power_off(inno);

	clk_disable_unprepare(inno->phyclk);

	dev_dbg(inno->dev, "Inno HDMI PHY Power Off\n");

	return 0;
}