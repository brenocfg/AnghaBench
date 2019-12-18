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
struct rockchip_typec_phy {scalar_t__ mode; int /*<<< orphan*/  lock; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int MODE_DFP_USB ; 
 scalar_t__ MODE_DISCONNECT ; 
 int MODE_UFP_USB ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rockchip_typec_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  tcphy_cfg_usb3_to_usb2_only (struct rockchip_typec_phy*,int) ; 
 int /*<<< orphan*/  tcphy_phy_deinit (struct rockchip_typec_phy*) ; 

__attribute__((used)) static int rockchip_usb3_phy_power_off(struct phy *phy)
{
	struct rockchip_typec_phy *tcphy = phy_get_drvdata(phy);

	mutex_lock(&tcphy->lock);
	tcphy_cfg_usb3_to_usb2_only(tcphy, false);

	if (tcphy->mode == MODE_DISCONNECT)
		goto unlock;

	tcphy->mode &= ~(MODE_UFP_USB | MODE_DFP_USB);
	if (tcphy->mode == MODE_DISCONNECT)
		tcphy_phy_deinit(tcphy);

unlock:
	mutex_unlock(&tcphy->lock);
	return 0;
}