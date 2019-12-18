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
struct phy_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ nicpm_base; } ;
struct bgmac {TYPE_2__* dev; int /*<<< orphan*/  net_dev; TYPE_1__ plat; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  bgmac_adjust_link ; 
 int /*<<< orphan*/  bgmac_nicpm_speed_set ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct phy_device* of_phy_get_and_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int platform_phy_connect(struct bgmac *bgmac)
{
	struct phy_device *phy_dev;

	if (bgmac->plat.nicpm_base)
		phy_dev = of_phy_get_and_connect(bgmac->net_dev,
						 bgmac->dev->of_node,
						 bgmac_nicpm_speed_set);
	else
		phy_dev = of_phy_get_and_connect(bgmac->net_dev,
						 bgmac->dev->of_node,
						 bgmac_adjust_link);
	if (!phy_dev) {
		dev_err(bgmac->dev, "PHY connection failed\n");
		return -ENODEV;
	}

	return 0;
}