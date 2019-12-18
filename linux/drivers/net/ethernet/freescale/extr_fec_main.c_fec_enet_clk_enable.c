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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct fec_enet_private {int ptp_clk_on; scalar_t__ clk_enet_out; scalar_t__ clk_ref; int /*<<< orphan*/  ptp_clk_mutex; scalar_t__ clk_ptp; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_reset_after_clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fec_enet_clk_enable(struct net_device *ndev, bool enable)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int ret;

	if (enable) {
		ret = clk_prepare_enable(fep->clk_enet_out);
		if (ret)
			return ret;

		if (fep->clk_ptp) {
			mutex_lock(&fep->ptp_clk_mutex);
			ret = clk_prepare_enable(fep->clk_ptp);
			if (ret) {
				mutex_unlock(&fep->ptp_clk_mutex);
				goto failed_clk_ptp;
			} else {
				fep->ptp_clk_on = true;
			}
			mutex_unlock(&fep->ptp_clk_mutex);
		}

		ret = clk_prepare_enable(fep->clk_ref);
		if (ret)
			goto failed_clk_ref;

		phy_reset_after_clk_enable(ndev->phydev);
	} else {
		clk_disable_unprepare(fep->clk_enet_out);
		if (fep->clk_ptp) {
			mutex_lock(&fep->ptp_clk_mutex);
			clk_disable_unprepare(fep->clk_ptp);
			fep->ptp_clk_on = false;
			mutex_unlock(&fep->ptp_clk_mutex);
		}
		clk_disable_unprepare(fep->clk_ref);
	}

	return 0;

failed_clk_ref:
	if (fep->clk_ref)
		clk_disable_unprepare(fep->clk_ref);
failed_clk_ptp:
	if (fep->clk_enet_out)
		clk_disable_unprepare(fep->clk_enet_out);

	return ret;
}