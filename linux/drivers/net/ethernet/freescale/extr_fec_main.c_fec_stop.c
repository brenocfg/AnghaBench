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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct fec_platform_data {int /*<<< orphan*/  (* sleep_mode_enable ) (int) ;} ;
struct fec_enet_private {int wol_flag; int quirks; int phy_speed; scalar_t__ hwp; scalar_t__ link; TYPE_2__* pdev; } ;
struct TYPE_3__ {struct fec_platform_data* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int FEC_DEFAULT_IMASK ; 
 scalar_t__ FEC_ECNTRL ; 
 int FEC_ECR_MAGICEN ; 
 int FEC_ECR_SLEEP ; 
 int FEC_ENET_GRA ; 
 int FEC_ENET_WAKEUP ; 
 scalar_t__ FEC_IEVENT ; 
 scalar_t__ FEC_IMASK ; 
 scalar_t__ FEC_MII_SPEED ; 
 int FEC_QUIRK_ENET_MAC ; 
 int FEC_QUIRK_HAS_AVB ; 
 scalar_t__ FEC_R_CNTRL ; 
 int FEC_WOL_FLAG_SLEEP_ON ; 
 scalar_t__ FEC_X_CNTRL ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
fec_stop(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct fec_platform_data *pdata = fep->pdev->dev.platform_data;
	u32 rmii_mode = readl(fep->hwp + FEC_R_CNTRL) & (1 << 8);
	u32 val;

	/* We cannot expect a graceful transmit stop without link !!! */
	if (fep->link) {
		writel(1, fep->hwp + FEC_X_CNTRL); /* Graceful transmit stop */
		udelay(10);
		if (!(readl(fep->hwp + FEC_IEVENT) & FEC_ENET_GRA))
			netdev_err(ndev, "Graceful transmit stop did not complete!\n");
	}

	/* Whack a reset.  We should wait for this.
	 * For i.MX6SX SOC, enet use AXI bus, we use disable MAC
	 * instead of reset MAC itself.
	 */
	if (!(fep->wol_flag & FEC_WOL_FLAG_SLEEP_ON)) {
		if (fep->quirks & FEC_QUIRK_HAS_AVB) {
			writel(0, fep->hwp + FEC_ECNTRL);
		} else {
			writel(1, fep->hwp + FEC_ECNTRL);
			udelay(10);
		}
		writel(FEC_DEFAULT_IMASK, fep->hwp + FEC_IMASK);
	} else {
		writel(FEC_DEFAULT_IMASK | FEC_ENET_WAKEUP, fep->hwp + FEC_IMASK);
		val = readl(fep->hwp + FEC_ECNTRL);
		val |= (FEC_ECR_MAGICEN | FEC_ECR_SLEEP);
		writel(val, fep->hwp + FEC_ECNTRL);

		if (pdata && pdata->sleep_mode_enable)
			pdata->sleep_mode_enable(true);
	}
	writel(fep->phy_speed, fep->hwp + FEC_MII_SPEED);

	/* We have to keep ENET enabled to have MII interrupt stay working */
	if (fep->quirks & FEC_QUIRK_ENET_MAC &&
		!(fep->wol_flag & FEC_WOL_FLAG_SLEEP_ON)) {
		writel(2, fep->hwp + FEC_ECNTRL);
		writel(rmii_mode, fep->hwp + FEC_R_CNTRL);
	}
}