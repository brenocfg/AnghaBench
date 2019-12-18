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
struct TYPE_4__ {int rx_chains_num; void* tx_chains_num; } ;
struct iwl_priv {TYPE_2__ hw_params; TYPE_1__* cfg; struct iwl_nvm_data* nvm_data; } ;
struct iwl_nvm_data {int /*<<< orphan*/  valid_rx_ant; int /*<<< orphan*/  valid_tx_ant; scalar_t__ sku_cap_11n_enable; scalar_t__ sku_cap_band_52ghz_enable; scalar_t__ sku_cap_band_24ghz_enable; } ;
struct TYPE_3__ {scalar_t__ rx_with_siso_diversity; int /*<<< orphan*/  ht_params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 void* num_of_ant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_eeprom_init_hw_params(struct iwl_priv *priv)
{
	struct iwl_nvm_data *data = priv->nvm_data;

	if (data->sku_cap_11n_enable &&
	    !priv->cfg->ht_params) {
		IWL_ERR(priv, "Invalid 11n configuration\n");
		return -EINVAL;
	}

	if (!data->sku_cap_11n_enable && !data->sku_cap_band_24ghz_enable &&
	    !data->sku_cap_band_52ghz_enable) {
		IWL_ERR(priv, "Invalid device sku\n");
		return -EINVAL;
	}

	IWL_DEBUG_INFO(priv,
		       "Device SKU: 24GHz %s %s, 52GHz %s %s, 11.n %s %s\n",
		       data->sku_cap_band_24ghz_enable ? "" : "NOT", "enabled",
		       data->sku_cap_band_52ghz_enable ? "" : "NOT", "enabled",
		       data->sku_cap_11n_enable ? "" : "NOT", "enabled");

	priv->hw_params.tx_chains_num =
		num_of_ant(data->valid_tx_ant);
	if (priv->cfg->rx_with_siso_diversity)
		priv->hw_params.rx_chains_num = 1;
	else
		priv->hw_params.rx_chains_num =
			num_of_ant(data->valid_rx_ant);

	IWL_DEBUG_INFO(priv, "Valid Tx ant: 0x%X, Valid Rx ant: 0x%X\n",
		       data->valid_tx_ant,
		       data->valid_rx_ant);

	return 0;
}