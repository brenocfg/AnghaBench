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
struct iwl_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_priv*,char*,int,int) ; 
 int RX_MPDU_RES_STATUS_DEC_DONE_MSK ; 
 int RX_MPDU_RES_STATUS_ICV_OK ; 
 int RX_MPDU_RES_STATUS_MIC_OK ; 
 int RX_MPDU_RES_STATUS_TTAK_OK ; 
 int RX_RES_STATUS_BAD_ICV_MIC ; 
 int RX_RES_STATUS_BAD_KEY_TTAK ; 
 int RX_RES_STATUS_DECRYPT_OK ; 
 int RX_RES_STATUS_NO_STATION_INFO_MISMATCH ; 
#define  RX_RES_STATUS_SEC_TYPE_CCMP 129 
 int RX_RES_STATUS_SEC_TYPE_ERR ; 
 int RX_RES_STATUS_SEC_TYPE_MSK ; 
 int RX_RES_STATUS_SEC_TYPE_NONE ; 
#define  RX_RES_STATUS_SEC_TYPE_TKIP 128 
 int RX_RES_STATUS_STATION_FOUND ; 

__attribute__((used)) static u32 iwlagn_translate_rx_status(struct iwl_priv *priv, u32 decrypt_in)
{
	u32 decrypt_out = 0;

	if ((decrypt_in & RX_RES_STATUS_STATION_FOUND) ==
					RX_RES_STATUS_STATION_FOUND)
		decrypt_out |= (RX_RES_STATUS_STATION_FOUND |
				RX_RES_STATUS_NO_STATION_INFO_MISMATCH);

	decrypt_out |= (decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK);

	/* packet was not encrypted */
	if ((decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK) ==
					RX_RES_STATUS_SEC_TYPE_NONE)
		return decrypt_out;

	/* packet was encrypted with unknown alg */
	if ((decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK) ==
					RX_RES_STATUS_SEC_TYPE_ERR)
		return decrypt_out;

	/* decryption was not done in HW */
	if ((decrypt_in & RX_MPDU_RES_STATUS_DEC_DONE_MSK) !=
					RX_MPDU_RES_STATUS_DEC_DONE_MSK)
		return decrypt_out;

	switch (decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK) {

	case RX_RES_STATUS_SEC_TYPE_CCMP:
		/* alg is CCM: check MIC only */
		if (!(decrypt_in & RX_MPDU_RES_STATUS_MIC_OK))
			/* Bad MIC */
			decrypt_out |= RX_RES_STATUS_BAD_ICV_MIC;
		else
			decrypt_out |= RX_RES_STATUS_DECRYPT_OK;

		break;

	case RX_RES_STATUS_SEC_TYPE_TKIP:
		if (!(decrypt_in & RX_MPDU_RES_STATUS_TTAK_OK)) {
			/* Bad TTAK */
			decrypt_out |= RX_RES_STATUS_BAD_KEY_TTAK;
			break;
		}
		/* fall through */
	default:
		if (!(decrypt_in & RX_MPDU_RES_STATUS_ICV_OK))
			decrypt_out |= RX_RES_STATUS_BAD_ICV_MIC;
		else
			decrypt_out |= RX_RES_STATUS_DECRYPT_OK;
		break;
	}

	IWL_DEBUG_RX(priv, "decrypt_in:0x%x  decrypt_out = 0x%x\n",
					decrypt_in, decrypt_out);

	return decrypt_out;
}