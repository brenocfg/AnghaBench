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
struct rockchip_typec_phy {scalar_t__ mode; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_MODE_CTL ; 
 int /*<<< orphan*/  DP_MODE_ENTER_A2 ; 
 scalar_t__ MODE_DFP_DP ; 
 scalar_t__ MODE_DISCONNECT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rockchip_typec_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  tcphy_phy_deinit (struct rockchip_typec_phy*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rockchip_dp_phy_power_off(struct phy *phy)
{
	struct rockchip_typec_phy *tcphy = phy_get_drvdata(phy);

	mutex_lock(&tcphy->lock);

	if (tcphy->mode == MODE_DISCONNECT)
		goto unlock;

	tcphy->mode &= ~MODE_DFP_DP;

	writel(DP_MODE_ENTER_A2, tcphy->base + DP_MODE_CTL);

	if (tcphy->mode == MODE_DISCONNECT)
		tcphy_phy_deinit(tcphy);

unlock:
	mutex_unlock(&tcphy->lock);
	return 0;
}