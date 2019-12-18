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
typedef  int u32 ;
typedef  int u16 ;
struct iwl_priv {TYPE_2__* contexts; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  flag; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_3__ {int filter_flags; } ;
struct TYPE_4__ {TYPE_1__ active; } ;

/* Variables and functions */
 int IEEE80211_FCTL_PROTECTED ; 
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_priv*,char*,...) ; 
 size_t IWL_RXON_CTX_BSS ; 
 int RXON_FILTER_DIS_DECRYPT_MSK ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int RX_RES_STATUS_BAD_ICV_MIC ; 
 int RX_RES_STATUS_BAD_KEY_TTAK ; 
 int RX_RES_STATUS_DECRYPT_OK ; 
 int RX_RES_STATUS_DECRYPT_TYPE_MSK ; 
#define  RX_RES_STATUS_SEC_TYPE_CCMP 130 
 int RX_RES_STATUS_SEC_TYPE_MSK ; 
#define  RX_RES_STATUS_SEC_TYPE_TKIP 129 
#define  RX_RES_STATUS_SEC_TYPE_WEP 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwlagn_set_decrypted_flag(struct iwl_priv *priv,
				  struct ieee80211_hdr *hdr,
				  u32 decrypt_res,
				  struct ieee80211_rx_status *stats)
{
	u16 fc = le16_to_cpu(hdr->frame_control);

	/*
	 * All contexts have the same setting here due to it being
	 * a module parameter, so OK to check any context.
	 */
	if (priv->contexts[IWL_RXON_CTX_BSS].active.filter_flags &
						RXON_FILTER_DIS_DECRYPT_MSK)
		return 0;

	if (!(fc & IEEE80211_FCTL_PROTECTED))
		return 0;

	IWL_DEBUG_RX(priv, "decrypt_res:0x%x\n", decrypt_res);
	switch (decrypt_res & RX_RES_STATUS_SEC_TYPE_MSK) {
	case RX_RES_STATUS_SEC_TYPE_TKIP:
		/* The uCode has got a bad phase 1 Key, pushes the packet.
		 * Decryption will be done in SW. */
		if ((decrypt_res & RX_RES_STATUS_DECRYPT_TYPE_MSK) ==
		    RX_RES_STATUS_BAD_KEY_TTAK)
			break;
		/* fall through */
	case RX_RES_STATUS_SEC_TYPE_WEP:
		if ((decrypt_res & RX_RES_STATUS_DECRYPT_TYPE_MSK) ==
		    RX_RES_STATUS_BAD_ICV_MIC) {
			/* bad ICV, the packet is destroyed since the
			 * decryption is inplace, drop it */
			IWL_DEBUG_RX(priv, "Packet destroyed\n");
			return -1;
		}
		/* fall through */
	case RX_RES_STATUS_SEC_TYPE_CCMP:
		if ((decrypt_res & RX_RES_STATUS_DECRYPT_TYPE_MSK) ==
		    RX_RES_STATUS_DECRYPT_OK) {
			IWL_DEBUG_RX(priv, "hw decrypt successfully!!!\n");
			stats->flag |= RX_FLAG_DECRYPTED;
		}
		break;

	default:
		break;
	}
	return 0;
}