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
struct ath10k {int dummy; } ;
typedef  enum htt_rx_mpdu_encrypt_type { ____Placeholder_htt_rx_mpdu_encrypt_type } htt_rx_mpdu_encrypt_type ;

/* Variables and functions */
#define  HTT_RX_MPDU_ENCRYPT_AES_CCM256_WPA2 138 
#define  HTT_RX_MPDU_ENCRYPT_AES_CCM_WPA2 137 
#define  HTT_RX_MPDU_ENCRYPT_AES_GCMP256_WPA2 136 
#define  HTT_RX_MPDU_ENCRYPT_AES_GCMP_WPA2 135 
#define  HTT_RX_MPDU_ENCRYPT_NONE 134 
#define  HTT_RX_MPDU_ENCRYPT_TKIP_WITHOUT_MIC 133 
#define  HTT_RX_MPDU_ENCRYPT_TKIP_WPA 132 
#define  HTT_RX_MPDU_ENCRYPT_WAPI 131 
#define  HTT_RX_MPDU_ENCRYPT_WEP104 130 
#define  HTT_RX_MPDU_ENCRYPT_WEP128 129 
#define  HTT_RX_MPDU_ENCRYPT_WEP40 128 
 int IEEE80211_TKIP_ICV_LEN ; 
 int IEEE80211_WEP_ICV_LEN ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 

__attribute__((used)) static int ath10k_htt_rx_crypto_icv_len(struct ath10k *ar,
					enum htt_rx_mpdu_encrypt_type type)
{
	switch (type) {
	case HTT_RX_MPDU_ENCRYPT_NONE:
	case HTT_RX_MPDU_ENCRYPT_AES_CCM_WPA2:
	case HTT_RX_MPDU_ENCRYPT_AES_CCM256_WPA2:
	case HTT_RX_MPDU_ENCRYPT_AES_GCMP_WPA2:
	case HTT_RX_MPDU_ENCRYPT_AES_GCMP256_WPA2:
		return 0;
	case HTT_RX_MPDU_ENCRYPT_WEP40:
	case HTT_RX_MPDU_ENCRYPT_WEP104:
		return IEEE80211_WEP_ICV_LEN;
	case HTT_RX_MPDU_ENCRYPT_TKIP_WITHOUT_MIC:
	case HTT_RX_MPDU_ENCRYPT_TKIP_WPA:
		return IEEE80211_TKIP_ICV_LEN;
	case HTT_RX_MPDU_ENCRYPT_WEP128:
	case HTT_RX_MPDU_ENCRYPT_WAPI:
		break;
	}

	ath10k_warn(ar, "unsupported encryption type %d\n", type);
	return 0;
}