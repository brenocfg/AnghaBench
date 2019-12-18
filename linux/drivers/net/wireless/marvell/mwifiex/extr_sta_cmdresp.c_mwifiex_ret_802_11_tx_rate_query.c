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
struct mwifiex_private {int /*<<< orphan*/  tx_htinfo; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  data_rate; int /*<<< orphan*/  is_data_rate_auto; } ;
struct TYPE_3__ {int /*<<< orphan*/  ht_info; int /*<<< orphan*/  tx_rate; } ;
struct TYPE_4__ {TYPE_1__ tx_rate; } ;
struct host_cmd_ds_command {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_index_to_data_rate (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_ret_802_11_tx_rate_query(struct mwifiex_private *priv,
					    struct host_cmd_ds_command *resp)
{
	priv->tx_rate = resp->params.tx_rate.tx_rate;
	priv->tx_htinfo = resp->params.tx_rate.ht_info;
	if (!priv->is_data_rate_auto)
		priv->data_rate =
			mwifiex_index_to_data_rate(priv, priv->tx_rate,
						   priv->tx_htinfo);

	return 0;
}