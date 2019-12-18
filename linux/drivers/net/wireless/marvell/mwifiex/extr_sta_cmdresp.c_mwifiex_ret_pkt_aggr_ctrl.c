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
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct TYPE_3__ {void* tx_aggr_align; void* tx_aggr_max_num; void* tx_aggr_max_size; int /*<<< orphan*/  mode; void* enable; } ;
struct mwifiex_adapter {TYPE_1__ bus_aggr; int /*<<< orphan*/  intf_hdr_len; } ;
struct host_cmd_ds_pkt_aggr_ctrl {int /*<<< orphan*/  tx_aggr_align; int /*<<< orphan*/  tx_aggr_max_num; int /*<<< orphan*/  tx_aggr_max_size; int /*<<< orphan*/  enable; } ;
struct TYPE_4__ {struct host_cmd_ds_pkt_aggr_ctrl pkt_aggr_ctrl; } ;
struct host_cmd_ds_command {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTF_HEADER_LEN ; 
 int /*<<< orphan*/  MWIFIEX_BUS_AGGR_MODE_LEN_V2 ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_ret_pkt_aggr_ctrl(struct mwifiex_private *priv,
				     struct host_cmd_ds_command *resp)
{
	struct host_cmd_ds_pkt_aggr_ctrl *pkt_aggr_ctrl =
					&resp->params.pkt_aggr_ctrl;
	struct mwifiex_adapter *adapter = priv->adapter;

	adapter->bus_aggr.enable = le16_to_cpu(pkt_aggr_ctrl->enable);
	if (adapter->bus_aggr.enable)
		adapter->intf_hdr_len = INTF_HEADER_LEN;
	adapter->bus_aggr.mode = MWIFIEX_BUS_AGGR_MODE_LEN_V2;
	adapter->bus_aggr.tx_aggr_max_size =
				le16_to_cpu(pkt_aggr_ctrl->tx_aggr_max_size);
	adapter->bus_aggr.tx_aggr_max_num =
				le16_to_cpu(pkt_aggr_ctrl->tx_aggr_max_num);
	adapter->bus_aggr.tx_aggr_align =
				le16_to_cpu(pkt_aggr_ctrl->tx_aggr_align);

	return 0;
}