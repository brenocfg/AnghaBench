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
struct TYPE_2__ {int protection; int /*<<< orphan*/  extension_chan_offset; int /*<<< orphan*/  enabled; } ;
struct iwl_rxon_cmd {int flags; } ;
struct iwl_rxon_context {TYPE_1__ ht; struct iwl_rxon_cmd staging; } ;
struct iwl_priv {int dummy; } ;
struct iwl_ht_config {int dummy; } ;

/* Variables and functions */
 int IEEE80211_HT_OP_MODE_PROTECTION_20MHZ ; 
#define  IEEE80211_HT_PARAM_CHA_SEC_ABOVE 130 
#define  IEEE80211_HT_PARAM_CHA_SEC_BELOW 129 
#define  IEEE80211_HT_PARAM_CHA_SEC_NONE 128 
 int /*<<< orphan*/  IWL_DEBUG_ASSOC (struct iwl_priv*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int RXON_FLG_CHANNEL_MODE_LEGACY ; 
 int RXON_FLG_CHANNEL_MODE_MIXED ; 
 int RXON_FLG_CHANNEL_MODE_MSK ; 
 int RXON_FLG_CHANNEL_MODE_PURE_40 ; 
 int RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK ; 
 int RXON_FLG_HT40_PROT_MSK ; 
 int RXON_FLG_HT_OPERATING_MODE_POS ; 
 int RXON_FLG_HT_PROT_MSK ; 
 int cpu_to_le32 (int) ; 
 scalar_t__ iwl_is_ht40_tx_allowed (struct iwl_priv*,struct iwl_rxon_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwlagn_set_rxon_chain (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int /*<<< orphan*/  le32_to_cpu (int) ; 

__attribute__((used)) static void _iwl_set_rxon_ht(struct iwl_priv *priv,
			     struct iwl_ht_config *ht_conf,
			     struct iwl_rxon_context *ctx)
{
	struct iwl_rxon_cmd *rxon = &ctx->staging;

	if (!ctx->ht.enabled) {
		rxon->flags &= ~(RXON_FLG_CHANNEL_MODE_MSK |
			RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK |
			RXON_FLG_HT40_PROT_MSK |
			RXON_FLG_HT_PROT_MSK);
		return;
	}

	/* FIXME: if the definition of ht.protection changed, the "translation"
	 * will be needed for rxon->flags
	 */
	rxon->flags |= cpu_to_le32(ctx->ht.protection <<
				   RXON_FLG_HT_OPERATING_MODE_POS);

	/* Set up channel bandwidth:
	 * 20 MHz only, 20/40 mixed or pure 40 if ht40 ok */
	/* clear the HT channel mode before set the mode */
	rxon->flags &= ~(RXON_FLG_CHANNEL_MODE_MSK |
			 RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK);
	if (iwl_is_ht40_tx_allowed(priv, ctx, NULL)) {
		/* pure ht40 */
		if (ctx->ht.protection ==
		    IEEE80211_HT_OP_MODE_PROTECTION_20MHZ) {
			rxon->flags |= RXON_FLG_CHANNEL_MODE_PURE_40;
			/*
			 * Note: control channel is opposite of extension
			 * channel
			 */
			switch (ctx->ht.extension_chan_offset) {
			case IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
				rxon->flags &=
					~RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				break;
			case IEEE80211_HT_PARAM_CHA_SEC_BELOW:
				rxon->flags |=
					RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				break;
			}
		} else {
			/*
			 * Note: control channel is opposite of extension
			 * channel
			 */
			switch (ctx->ht.extension_chan_offset) {
			case IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
				rxon->flags &=
					~(RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK);
				rxon->flags |= RXON_FLG_CHANNEL_MODE_MIXED;
				break;
			case IEEE80211_HT_PARAM_CHA_SEC_BELOW:
				rxon->flags |= RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				rxon->flags |= RXON_FLG_CHANNEL_MODE_MIXED;
				break;
			case IEEE80211_HT_PARAM_CHA_SEC_NONE:
			default:
				/*
				 * channel location only valid if in Mixed
				 * mode
				 */
				IWL_ERR(priv,
					"invalid extension channel offset\n");
				break;
			}
		}
	} else {
		rxon->flags |= RXON_FLG_CHANNEL_MODE_LEGACY;
	}

	iwlagn_set_rxon_chain(priv, ctx);

	IWL_DEBUG_ASSOC(priv, "rxon flags 0x%X operation mode :0x%X "
			"extension channel offset 0x%x\n",
			le32_to_cpu(rxon->flags), ctx->ht.protection,
			ctx->ht.extension_chan_offset);
}