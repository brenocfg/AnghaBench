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
struct ethtool_eee {int tx_lpi_timer; scalar_t__ tx_lpi_enabled; scalar_t__ eee_enabled; int /*<<< orphan*/  advertised; } ;
struct TYPE_4__ {int eee_mode; } ;
struct TYPE_3__ {int eee_status; } ;
struct bnx2x {TYPE_2__ link_params; TYPE_1__ link_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 size_t BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int EEE_MODE_ADV_LPI ; 
 int EEE_MODE_ENABLE_LPI ; 
 int EEE_MODE_NVRAM_AGGRESSIVE_TIME ; 
 int EEE_MODE_OUTPUT_TIME ; 
 int EEE_MODE_OVERRIDE_NVRAM ; 
 int EEE_MODE_TIMER_MASK ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_MF (struct bnx2x*) ; 
 int /*<<< orphan*/  SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int SHMEM_EEE_ADV_STATUS_MASK ; 
 int /*<<< orphan*/  SHMEM_EEE_ADV_STATUS_SHIFT ; 
 int SHMEM_EEE_SUPPORTED_MASK ; 
 int /*<<< orphan*/  STATS_EVENT_STOP ; 
 int bnx2x_adv_to_eee (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_force_link_reset (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_link_set (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_stats_handle (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * eee_status ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int bnx2x_set_eee(struct net_device *dev, struct ethtool_eee *edata)
{
	struct bnx2x *bp = netdev_priv(dev);
	u32 eee_cfg;
	u32 advertised;

	if (IS_MF(bp))
		return 0;

	if (!SHMEM2_HAS(bp, eee_status[BP_PORT(bp)])) {
		DP(BNX2X_MSG_ETHTOOL, "BC Version does not support EEE\n");
		return -EOPNOTSUPP;
	}

	eee_cfg = bp->link_vars.eee_status;

	if (!(eee_cfg & SHMEM_EEE_SUPPORTED_MASK)) {
		DP(BNX2X_MSG_ETHTOOL, "Board does not support EEE!\n");
		return -EOPNOTSUPP;
	}

	advertised = bnx2x_adv_to_eee(edata->advertised,
				      SHMEM_EEE_ADV_STATUS_SHIFT);
	if ((advertised != (eee_cfg & SHMEM_EEE_ADV_STATUS_MASK))) {
		DP(BNX2X_MSG_ETHTOOL,
		   "Direct manipulation of EEE advertisement is not supported\n");
		return -EINVAL;
	}

	if (edata->tx_lpi_timer > EEE_MODE_TIMER_MASK) {
		DP(BNX2X_MSG_ETHTOOL,
		   "Maximal Tx Lpi timer supported is %x(u)\n",
		   EEE_MODE_TIMER_MASK);
		return -EINVAL;
	}
	if (edata->tx_lpi_enabled &&
	    (edata->tx_lpi_timer < EEE_MODE_NVRAM_AGGRESSIVE_TIME)) {
		DP(BNX2X_MSG_ETHTOOL,
		   "Minimal Tx Lpi timer supported is %d(u)\n",
		   EEE_MODE_NVRAM_AGGRESSIVE_TIME);
		return -EINVAL;
	}

	/* All is well; Apply changes*/
	if (edata->eee_enabled)
		bp->link_params.eee_mode |= EEE_MODE_ADV_LPI;
	else
		bp->link_params.eee_mode &= ~EEE_MODE_ADV_LPI;

	if (edata->tx_lpi_enabled)
		bp->link_params.eee_mode |= EEE_MODE_ENABLE_LPI;
	else
		bp->link_params.eee_mode &= ~EEE_MODE_ENABLE_LPI;

	bp->link_params.eee_mode &= ~EEE_MODE_TIMER_MASK;
	bp->link_params.eee_mode |= (edata->tx_lpi_timer &
				    EEE_MODE_TIMER_MASK) |
				    EEE_MODE_OVERRIDE_NVRAM |
				    EEE_MODE_OUTPUT_TIME;

	/* Restart link to propagate changes */
	if (netif_running(dev)) {
		bnx2x_stats_handle(bp, STATS_EVENT_STOP);
		bnx2x_force_link_reset(bp);
		bnx2x_link_set(bp);
	}

	return 0;
}