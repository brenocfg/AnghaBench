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
struct iwl_rxon_cmd {scalar_t__ flags; scalar_t__ filter_flags; scalar_t__ cck_basic_rates; scalar_t__ ofdm_ht_single_stream_basic_rates; scalar_t__ ofdm_ht_dual_stream_basic_rates; scalar_t__ ofdm_ht_triple_stream_basic_rates; scalar_t__ acquisition_data; scalar_t__ rx_chain; scalar_t__ ofdm_basic_rates; } ;
struct iwl_rxon_context {int /*<<< orphan*/  rxon_assoc_cmd; struct iwl_rxon_cmd staging; struct iwl_rxon_cmd active; } ;
struct iwl_rxon_assoc_cmd {scalar_t__ flags; scalar_t__ filter_flags; scalar_t__ ofdm_basic_rates; scalar_t__ cck_basic_rates; scalar_t__ ofdm_ht_single_stream_basic_rates; scalar_t__ ofdm_ht_dual_stream_basic_rates; scalar_t__ rx_chain_select_flags; scalar_t__ ofdm_ht_triple_stream_basic_rates; scalar_t__ acquisition_data; scalar_t__ reserved3; scalar_t__ reserved2; scalar_t__ reserved1; } ;
struct iwl_priv {int dummy; } ;
typedef  int /*<<< orphan*/  rxon_assoc ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*) ; 
 int iwl_dvm_send_cmd_pdu (struct iwl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_rxon_assoc_cmd*) ; 

__attribute__((used)) static int iwlagn_send_rxon_assoc(struct iwl_priv *priv,
				  struct iwl_rxon_context *ctx)
{
	int ret = 0;
	struct iwl_rxon_assoc_cmd rxon_assoc;
	const struct iwl_rxon_cmd *rxon1 = &ctx->staging;
	const struct iwl_rxon_cmd *rxon2 = &ctx->active;

	if ((rxon1->flags == rxon2->flags) &&
	    (rxon1->filter_flags == rxon2->filter_flags) &&
	    (rxon1->cck_basic_rates == rxon2->cck_basic_rates) &&
	    (rxon1->ofdm_ht_single_stream_basic_rates ==
	     rxon2->ofdm_ht_single_stream_basic_rates) &&
	    (rxon1->ofdm_ht_dual_stream_basic_rates ==
	     rxon2->ofdm_ht_dual_stream_basic_rates) &&
	    (rxon1->ofdm_ht_triple_stream_basic_rates ==
	     rxon2->ofdm_ht_triple_stream_basic_rates) &&
	    (rxon1->acquisition_data == rxon2->acquisition_data) &&
	    (rxon1->rx_chain == rxon2->rx_chain) &&
	    (rxon1->ofdm_basic_rates == rxon2->ofdm_basic_rates)) {
		IWL_DEBUG_INFO(priv, "Using current RXON_ASSOC.  Not resending.\n");
		return 0;
	}

	rxon_assoc.flags = ctx->staging.flags;
	rxon_assoc.filter_flags = ctx->staging.filter_flags;
	rxon_assoc.ofdm_basic_rates = ctx->staging.ofdm_basic_rates;
	rxon_assoc.cck_basic_rates = ctx->staging.cck_basic_rates;
	rxon_assoc.reserved1 = 0;
	rxon_assoc.reserved2 = 0;
	rxon_assoc.reserved3 = 0;
	rxon_assoc.ofdm_ht_single_stream_basic_rates =
	    ctx->staging.ofdm_ht_single_stream_basic_rates;
	rxon_assoc.ofdm_ht_dual_stream_basic_rates =
	    ctx->staging.ofdm_ht_dual_stream_basic_rates;
	rxon_assoc.rx_chain_select_flags = ctx->staging.rx_chain;
	rxon_assoc.ofdm_ht_triple_stream_basic_rates =
		 ctx->staging.ofdm_ht_triple_stream_basic_rates;
	rxon_assoc.acquisition_data = ctx->staging.acquisition_data;

	ret = iwl_dvm_send_cmd_pdu(priv, ctx->rxon_assoc_cmd,
				CMD_ASYNC, sizeof(rxon_assoc), &rxon_assoc);
	return ret;
}