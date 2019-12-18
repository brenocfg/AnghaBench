#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {char* name; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_type; int /*<<< orphan*/  rx_filter; } ;
struct TYPE_10__ {int max_adj; int pps; void* enable; void* settime64; void* gettimex64; void* adjtime; void* adjfreq; int /*<<< orphan*/  n_per_out; int /*<<< orphan*/  n_ext_ts; int /*<<< orphan*/  n_alarm; void* owner; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int type; } ;
struct TYPE_7__ {TYPE_1__ mac; } ;
struct ixgbe_adapter {TYPE_4__ tstamp_config; int /*<<< orphan*/ * ptp_clock; TYPE_3__* pdev; TYPE_5__ ptp_caps; int /*<<< orphan*/ * ptp_setup_sdp; TYPE_2__ hw; struct net_device* netdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long EOPNOTSUPP ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_NONE ; 
 int /*<<< orphan*/  HWTSTAMP_TX_OFF ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 long PTR_ERR (int /*<<< orphan*/ *) ; 
 void* THIS_MODULE ; 
 int /*<<< orphan*/  e_dev_err (char*) ; 
 int /*<<< orphan*/  e_dev_info (char*,char*) ; 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_x 129 
#define  ixgbe_mac_x550em_a 128 
 void* ixgbe_ptp_adjfreq_82599 ; 
 void* ixgbe_ptp_adjfreq_X550 ; 
 void* ixgbe_ptp_adjtime ; 
 void* ixgbe_ptp_feature_enable ; 
 void* ixgbe_ptp_gettimex ; 
 void* ixgbe_ptp_settime ; 
 int /*<<< orphan*/ * ixgbe_ptp_setup_sdp_X540 ; 
 int /*<<< orphan*/ * ixgbe_ptp_setup_sdp_X550 ; 
 int /*<<< orphan*/ * ptp_clock_register (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static long ixgbe_ptp_create_clock(struct ixgbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	long err;

	/* do nothing if we already have a clock device */
	if (!IS_ERR_OR_NULL(adapter->ptp_clock))
		return 0;

	switch (adapter->hw.mac.type) {
	case ixgbe_mac_X540:
		snprintf(adapter->ptp_caps.name,
			 sizeof(adapter->ptp_caps.name),
			 "%s", netdev->name);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 250000000;
		adapter->ptp_caps.n_alarm = 0;
		adapter->ptp_caps.n_ext_ts = 0;
		adapter->ptp_caps.n_per_out = 0;
		adapter->ptp_caps.pps = 1;
		adapter->ptp_caps.adjfreq = ixgbe_ptp_adjfreq_82599;
		adapter->ptp_caps.adjtime = ixgbe_ptp_adjtime;
		adapter->ptp_caps.gettimex64 = ixgbe_ptp_gettimex;
		adapter->ptp_caps.settime64 = ixgbe_ptp_settime;
		adapter->ptp_caps.enable = ixgbe_ptp_feature_enable;
		adapter->ptp_setup_sdp = ixgbe_ptp_setup_sdp_X540;
		break;
	case ixgbe_mac_82599EB:
		snprintf(adapter->ptp_caps.name,
			 sizeof(adapter->ptp_caps.name),
			 "%s", netdev->name);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 250000000;
		adapter->ptp_caps.n_alarm = 0;
		adapter->ptp_caps.n_ext_ts = 0;
		adapter->ptp_caps.n_per_out = 0;
		adapter->ptp_caps.pps = 0;
		adapter->ptp_caps.adjfreq = ixgbe_ptp_adjfreq_82599;
		adapter->ptp_caps.adjtime = ixgbe_ptp_adjtime;
		adapter->ptp_caps.gettimex64 = ixgbe_ptp_gettimex;
		adapter->ptp_caps.settime64 = ixgbe_ptp_settime;
		adapter->ptp_caps.enable = ixgbe_ptp_feature_enable;
		break;
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		snprintf(adapter->ptp_caps.name, 16, "%s", netdev->name);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 30000000;
		adapter->ptp_caps.n_alarm = 0;
		adapter->ptp_caps.n_ext_ts = 0;
		adapter->ptp_caps.n_per_out = 0;
		adapter->ptp_caps.pps = 1;
		adapter->ptp_caps.adjfreq = ixgbe_ptp_adjfreq_X550;
		adapter->ptp_caps.adjtime = ixgbe_ptp_adjtime;
		adapter->ptp_caps.gettimex64 = ixgbe_ptp_gettimex;
		adapter->ptp_caps.settime64 = ixgbe_ptp_settime;
		adapter->ptp_caps.enable = ixgbe_ptp_feature_enable;
		adapter->ptp_setup_sdp = ixgbe_ptp_setup_sdp_X550;
		break;
	default:
		adapter->ptp_clock = NULL;
		adapter->ptp_setup_sdp = NULL;
		return -EOPNOTSUPP;
	}

	adapter->ptp_clock = ptp_clock_register(&adapter->ptp_caps,
						&adapter->pdev->dev);
	if (IS_ERR(adapter->ptp_clock)) {
		err = PTR_ERR(adapter->ptp_clock);
		adapter->ptp_clock = NULL;
		e_dev_err("ptp_clock_register failed\n");
		return err;
	} else if (adapter->ptp_clock)
		e_dev_info("registered PHC device on %s\n", netdev->name);

	/* set default timestamp mode to disabled here. We do this in
	 * create_clock instead of init, because we don't want to override the
	 * previous settings during a resume cycle.
	 */
	adapter->tstamp_config.rx_filter = HWTSTAMP_FILTER_NONE;
	adapter->tstamp_config.tx_type = HWTSTAMP_TX_OFF;

	return 0;
}