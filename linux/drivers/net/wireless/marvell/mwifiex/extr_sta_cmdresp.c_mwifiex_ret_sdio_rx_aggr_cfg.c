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
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int /*<<< orphan*/  sdio_rx_block_size; int /*<<< orphan*/  sdio_rx_aggr_enable; } ;
struct host_cmd_sdio_sp_rx_aggr_cfg {int /*<<< orphan*/  block_size; int /*<<< orphan*/  enable; } ;
struct TYPE_2__ {struct host_cmd_sdio_sp_rx_aggr_cfg sdio_rx_aggr_cfg; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_ret_sdio_rx_aggr_cfg(struct mwifiex_private *priv,
					struct host_cmd_ds_command *resp)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct host_cmd_sdio_sp_rx_aggr_cfg *cfg =
				&resp->params.sdio_rx_aggr_cfg;

	adapter->sdio_rx_aggr_enable = cfg->enable;
	adapter->sdio_rx_block_size = le16_to_cpu(cfg->block_size);

	return 0;
}