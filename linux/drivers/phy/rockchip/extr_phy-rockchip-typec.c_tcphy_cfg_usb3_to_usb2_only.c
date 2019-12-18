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
struct rockchip_usb3phy_port_cfg {int /*<<< orphan*/  usb3_host_port; int /*<<< orphan*/  usb3_host_disable; int /*<<< orphan*/  usb3tousb2_en; } ;
struct rockchip_typec_phy {struct rockchip_usb3phy_port_cfg* port_cfgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  property_enable (struct rockchip_typec_phy*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tcphy_cfg_usb3_to_usb2_only(struct rockchip_typec_phy *tcphy,
				       bool value)
{
	const struct rockchip_usb3phy_port_cfg *cfg = tcphy->port_cfgs;

	property_enable(tcphy, &cfg->usb3tousb2_en, value);
	property_enable(tcphy, &cfg->usb3_host_disable, value);
	property_enable(tcphy, &cfg->usb3_host_port, !value);

	return 0;
}