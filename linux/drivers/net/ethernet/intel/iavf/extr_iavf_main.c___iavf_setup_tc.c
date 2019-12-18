#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u16 ;
struct virtchnl_vf_resource {int vf_cap_flags; } ;
struct TYPE_8__ {int num_tc; scalar_t__* count; scalar_t__* offset; int /*<<< orphan*/  hw; } ;
struct tc_mqprio_qopt_offload {scalar_t__ mode; TYPE_4__ qopt; int /*<<< orphan*/ * max_rate; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {scalar_t__ state; int total_qps; TYPE_2__* ch_info; } ;
struct iavf_adapter {int num_tc; int /*<<< orphan*/  netdev; int /*<<< orphan*/  aq_required; TYPE_3__ ch_config; TYPE_1__* pdev; struct virtchnl_vf_resource* vf_res; } ;
struct TYPE_6__ {scalar_t__ count; scalar_t__ offset; int /*<<< orphan*/  max_tx_rate; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_DISABLE_CHANNELS ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_ENABLE_CHANNELS ; 
 int IAVF_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  IAVF_MBPS_DIVISOR ; 
 scalar_t__ TC_MQPRIO_MODE_CHANNEL ; 
 int VIRTCHNL_VF_OFFLOAD_ADQ ; 
 scalar_t__ __IAVF_TC_INVALID ; 
 scalar_t__ __IAVF_TC_RUNNING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_del_all_cloud_filters (struct iavf_adapter*) ; 
 int iavf_validate_ch_config (struct iavf_adapter*,struct tc_mqprio_qopt_offload*) ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_reset_tc (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_num_tc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_set_tc_queue (struct net_device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 

__attribute__((used)) static int __iavf_setup_tc(struct net_device *netdev, void *type_data)
{
	struct tc_mqprio_qopt_offload *mqprio_qopt = type_data;
	struct iavf_adapter *adapter = netdev_priv(netdev);
	struct virtchnl_vf_resource *vfres = adapter->vf_res;
	u8 num_tc = 0, total_qps = 0;
	int ret = 0, netdev_tc = 0;
	u64 max_tx_rate;
	u16 mode;
	int i;

	num_tc = mqprio_qopt->qopt.num_tc;
	mode = mqprio_qopt->mode;

	/* delete queue_channel */
	if (!mqprio_qopt->qopt.hw) {
		if (adapter->ch_config.state == __IAVF_TC_RUNNING) {
			/* reset the tc configuration */
			netdev_reset_tc(netdev);
			adapter->num_tc = 0;
			netif_tx_stop_all_queues(netdev);
			netif_tx_disable(netdev);
			iavf_del_all_cloud_filters(adapter);
			adapter->aq_required = IAVF_FLAG_AQ_DISABLE_CHANNELS;
			goto exit;
		} else {
			return -EINVAL;
		}
	}

	/* add queue channel */
	if (mode == TC_MQPRIO_MODE_CHANNEL) {
		if (!(vfres->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_ADQ)) {
			dev_err(&adapter->pdev->dev, "ADq not supported\n");
			return -EOPNOTSUPP;
		}
		if (adapter->ch_config.state != __IAVF_TC_INVALID) {
			dev_err(&adapter->pdev->dev, "TC configuration already exists\n");
			return -EINVAL;
		}

		ret = iavf_validate_ch_config(adapter, mqprio_qopt);
		if (ret)
			return ret;
		/* Return if same TC config is requested */
		if (adapter->num_tc == num_tc)
			return 0;
		adapter->num_tc = num_tc;

		for (i = 0; i < IAVF_MAX_TRAFFIC_CLASS; i++) {
			if (i < num_tc) {
				adapter->ch_config.ch_info[i].count =
					mqprio_qopt->qopt.count[i];
				adapter->ch_config.ch_info[i].offset =
					mqprio_qopt->qopt.offset[i];
				total_qps += mqprio_qopt->qopt.count[i];
				max_tx_rate = mqprio_qopt->max_rate[i];
				/* convert to Mbps */
				max_tx_rate = div_u64(max_tx_rate,
						      IAVF_MBPS_DIVISOR);
				adapter->ch_config.ch_info[i].max_tx_rate =
					max_tx_rate;
			} else {
				adapter->ch_config.ch_info[i].count = 1;
				adapter->ch_config.ch_info[i].offset = 0;
			}
		}
		adapter->ch_config.total_qps = total_qps;
		netif_tx_stop_all_queues(netdev);
		netif_tx_disable(netdev);
		adapter->aq_required |= IAVF_FLAG_AQ_ENABLE_CHANNELS;
		netdev_reset_tc(netdev);
		/* Report the tc mapping up the stack */
		netdev_set_num_tc(adapter->netdev, num_tc);
		for (i = 0; i < IAVF_MAX_TRAFFIC_CLASS; i++) {
			u16 qcount = mqprio_qopt->qopt.count[i];
			u16 qoffset = mqprio_qopt->qopt.offset[i];

			if (i < num_tc)
				netdev_set_tc_queue(netdev, netdev_tc++, qcount,
						    qoffset);
		}
	}
exit:
	return ret;
}