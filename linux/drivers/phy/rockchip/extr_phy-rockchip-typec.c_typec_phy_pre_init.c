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
struct rockchip_usb3phy_port_cfg {int /*<<< orphan*/  usb3tousb2_en; int /*<<< orphan*/  external_psm; } ;
struct rockchip_typec_phy {int /*<<< orphan*/  mode; int /*<<< orphan*/  pipe_rst; int /*<<< orphan*/  uphy_rst; int /*<<< orphan*/  tcphy_rst; struct rockchip_usb3phy_port_cfg* port_cfgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_DISCONNECT ; 
 int /*<<< orphan*/  property_enable (struct rockchip_typec_phy*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void typec_phy_pre_init(struct rockchip_typec_phy *tcphy)
{
	const struct rockchip_usb3phy_port_cfg *cfg = tcphy->port_cfgs;

	reset_control_assert(tcphy->tcphy_rst);
	reset_control_assert(tcphy->uphy_rst);
	reset_control_assert(tcphy->pipe_rst);

	/* select external psm clock */
	property_enable(tcphy, &cfg->external_psm, 1);
	property_enable(tcphy, &cfg->usb3tousb2_en, 0);

	tcphy->mode = MODE_DISCONNECT;
}