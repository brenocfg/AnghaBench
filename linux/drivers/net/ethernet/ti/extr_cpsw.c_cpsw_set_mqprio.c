#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int num_tc; int* prio_tc_map; int* count; int* offset; scalar_t__ hw; } ;
struct tc_mqprio_qopt_offload {scalar_t__ mode; TYPE_1__ qopt; } ;
struct net_device {int dummy; } ;
struct cpsw_slave {int dummy; } ;
struct cpsw_priv {scalar_t__ mqprio_hw; struct cpsw_common* cpsw; } ;
struct cpsw_common {scalar_t__ version; int /*<<< orphan*/  dev; struct cpsw_slave* slaves; } ;

/* Variables and functions */
 int CPSW1_TX_PRI_MAP ; 
 int CPSW2_TX_PRI_MAP ; 
 int CPSW_TC_NUM ; 
 scalar_t__ CPSW_VERSION_1 ; 
 int EINVAL ; 
 scalar_t__ TC_MQPRIO_MODE_DCB ; 
 int TX_PRIORITY_MAPPING ; 
 size_t cpsw_slave_index (struct cpsw_common*,struct cpsw_priv*) ; 
 int cpsw_tc_to_fifo (int,int) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_reset_tc (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_num_tc (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_set_tc_queue (struct net_device*,int,int,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slave_write (struct cpsw_slave*,int,int) ; 

__attribute__((used)) static int cpsw_set_mqprio(struct net_device *ndev, void *type_data)
{
	struct tc_mqprio_qopt_offload *mqprio = type_data;
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	int fifo, num_tc, count, offset;
	struct cpsw_slave *slave;
	u32 tx_prio_map = 0;
	int i, tc, ret;

	num_tc = mqprio->qopt.num_tc;
	if (num_tc > CPSW_TC_NUM)
		return -EINVAL;

	if (mqprio->mode != TC_MQPRIO_MODE_DCB)
		return -EINVAL;

	ret = pm_runtime_get_sync(cpsw->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(cpsw->dev);
		return ret;
	}

	if (num_tc) {
		for (i = 0; i < 8; i++) {
			tc = mqprio->qopt.prio_tc_map[i];
			fifo = cpsw_tc_to_fifo(tc, num_tc);
			tx_prio_map |= fifo << (4 * i);
		}

		netdev_set_num_tc(ndev, num_tc);
		for (i = 0; i < num_tc; i++) {
			count = mqprio->qopt.count[i];
			offset = mqprio->qopt.offset[i];
			netdev_set_tc_queue(ndev, i, count, offset);
		}
	}

	if (!mqprio->qopt.hw) {
		/* restore default configuration */
		netdev_reset_tc(ndev);
		tx_prio_map = TX_PRIORITY_MAPPING;
	}

	priv->mqprio_hw = mqprio->qopt.hw;

	offset = cpsw->version == CPSW_VERSION_1 ?
		 CPSW1_TX_PRI_MAP : CPSW2_TX_PRI_MAP;

	slave = &cpsw->slaves[cpsw_slave_index(cpsw, priv)];
	slave_write(slave, tx_prio_map, offset);

	pm_runtime_put_sync(cpsw->dev);

	return 0;
}