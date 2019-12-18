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
struct ethtool_eee {scalar_t__ advertised; scalar_t__ tx_lpi_timer; } ;
struct tg3 {int phy_flags; int /*<<< orphan*/  dev; struct ethtool_eee eee; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ TG3_CPMU_DBTMR1_LNKIDLE_MAX ; 
 int TG3_PHYFLG_EEE_CAP ; 
 int TG3_PHYFLG_USER_CONFIGURED ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_full_lock (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_full_unlock (struct tg3*) ; 
 int /*<<< orphan*/  tg3_phy_reset (struct tg3*) ; 
 int /*<<< orphan*/  tg3_setup_eee (struct tg3*) ; 
 int /*<<< orphan*/  tg3_warn_mgmt_link_flap (struct tg3*) ; 

__attribute__((used)) static int tg3_set_eee(struct net_device *dev, struct ethtool_eee *edata)
{
	struct tg3 *tp = netdev_priv(dev);

	if (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP)) {
		netdev_warn(tp->dev, "Board does not support EEE!\n");
		return -EOPNOTSUPP;
	}

	if (edata->advertised != tp->eee.advertised) {
		netdev_warn(tp->dev,
			    "Direct manipulation of EEE advertisement is not supported\n");
		return -EINVAL;
	}

	if (edata->tx_lpi_timer > TG3_CPMU_DBTMR1_LNKIDLE_MAX) {
		netdev_warn(tp->dev,
			    "Maximal Tx Lpi timer supported is %#x(u)\n",
			    TG3_CPMU_DBTMR1_LNKIDLE_MAX);
		return -EINVAL;
	}

	tp->eee = *edata;

	tp->phy_flags |= TG3_PHYFLG_USER_CONFIGURED;
	tg3_warn_mgmt_link_flap(tp);

	if (netif_running(tp->dev)) {
		tg3_full_lock(tp, 0);
		tg3_setup_eee(tp);
		tg3_phy_reset(tp);
		tg3_full_unlock(tp);
	}

	return 0;
}