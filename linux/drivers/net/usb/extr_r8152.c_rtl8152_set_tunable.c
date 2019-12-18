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
typedef  int /*<<< orphan*/  u32 ;
struct r8152 {int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_copybreak; } ;
struct net_device {int dummy; } ;
struct ethtool_tunable {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_RX_COPYBREAK 128 
 int /*<<< orphan*/  ETH_ZLEN ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct r8152*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  rx_err ; 

__attribute__((used)) static int rtl8152_set_tunable(struct net_device *netdev,
			       const struct ethtool_tunable *tunable,
			       const void *d)
{
	struct r8152 *tp = netdev_priv(netdev);
	u32 val;

	switch (tunable->id) {
	case ETHTOOL_RX_COPYBREAK:
		val = *(u32 *)d;
		if (val < ETH_ZLEN) {
			netif_err(tp, rx_err, netdev,
				  "Invalid rx copy break value\n");
			return -EINVAL;
		}

		if (tp->rx_copybreak != val) {
			napi_disable(&tp->napi);
			tp->rx_copybreak = val;
			napi_enable(&tp->napi);
		}
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}