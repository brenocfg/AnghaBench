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
typedef  int u32 ;
struct iwl_rxon_cmd {int flags; int* node_addr; int* bssid_addr; int ofdm_basic_rates; int cck_basic_rates; scalar_t__ assoc_id; scalar_t__ channel; } ;
struct iwl_rxon_context {struct iwl_rxon_cmd staging; } ;
struct iwl_priv {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int IWL_RATE_1M_MASK ; 
 int IWL_RATE_6M_MASK ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_priv*,char*) ; 
 int RXON_FLG_AUTO_DETECT_MSK ; 
 int RXON_FLG_BAND_24G_MSK ; 
 int RXON_FLG_CCK_MSK ; 
 int RXON_FLG_RADAR_DETECT_MSK ; 
 int RXON_FLG_SHORT_SLOT_MSK ; 
 int RXON_FLG_TGG_PROTECT_MSK ; 
 int RXON_FLG_TGJ_NARROW_BAND_MSK ; 
 int /*<<< orphan*/  WARN (int,char*,int,int) ; 
 int le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static int iwl_check_rxon_cmd(struct iwl_priv *priv,
			      struct iwl_rxon_context *ctx)
{
	struct iwl_rxon_cmd *rxon = &ctx->staging;
	u32 errors = 0;

	if (rxon->flags & RXON_FLG_BAND_24G_MSK) {
		if (rxon->flags & RXON_FLG_TGJ_NARROW_BAND_MSK) {
			IWL_WARN(priv, "check 2.4G: wrong narrow\n");
			errors |= BIT(0);
		}
		if (rxon->flags & RXON_FLG_RADAR_DETECT_MSK) {
			IWL_WARN(priv, "check 2.4G: wrong radar\n");
			errors |= BIT(1);
		}
	} else {
		if (!(rxon->flags & RXON_FLG_SHORT_SLOT_MSK)) {
			IWL_WARN(priv, "check 5.2G: not short slot!\n");
			errors |= BIT(2);
		}
		if (rxon->flags & RXON_FLG_CCK_MSK) {
			IWL_WARN(priv, "check 5.2G: CCK!\n");
			errors |= BIT(3);
		}
	}
	if ((rxon->node_addr[0] | rxon->bssid_addr[0]) & 0x1) {
		IWL_WARN(priv, "mac/bssid mcast!\n");
		errors |= BIT(4);
	}

	/* make sure basic rates 6Mbps and 1Mbps are supported */
	if ((rxon->ofdm_basic_rates & IWL_RATE_6M_MASK) == 0 &&
	    (rxon->cck_basic_rates & IWL_RATE_1M_MASK) == 0) {
		IWL_WARN(priv, "neither 1 nor 6 are basic\n");
		errors |= BIT(5);
	}

	if (le16_to_cpu(rxon->assoc_id) > 2007) {
		IWL_WARN(priv, "aid > 2007\n");
		errors |= BIT(6);
	}

	if ((rxon->flags & (RXON_FLG_CCK_MSK | RXON_FLG_SHORT_SLOT_MSK))
			== (RXON_FLG_CCK_MSK | RXON_FLG_SHORT_SLOT_MSK)) {
		IWL_WARN(priv, "CCK and short slot\n");
		errors |= BIT(7);
	}

	if ((rxon->flags & (RXON_FLG_CCK_MSK | RXON_FLG_AUTO_DETECT_MSK))
			== (RXON_FLG_CCK_MSK | RXON_FLG_AUTO_DETECT_MSK)) {
		IWL_WARN(priv, "CCK and auto detect\n");
		errors |= BIT(8);
	}

	if ((rxon->flags & (RXON_FLG_AUTO_DETECT_MSK |
			    RXON_FLG_TGG_PROTECT_MSK)) ==
			    RXON_FLG_TGG_PROTECT_MSK) {
		IWL_WARN(priv, "TGg but no auto-detect\n");
		errors |= BIT(9);
	}

	if (rxon->channel == 0) {
		IWL_WARN(priv, "zero channel is invalid\n");
		errors |= BIT(10);
	}

	WARN(errors, "Invalid RXON (%#x), channel %d",
	     errors, le16_to_cpu(rxon->channel));

	return errors ? -EINVAL : 0;
}