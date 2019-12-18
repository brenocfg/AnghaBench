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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm_rx_phy_data {int info_type; int /*<<< orphan*/  d0; int /*<<< orphan*/  d1; int /*<<< orphan*/  d4; int /*<<< orphan*/  d2; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ieee80211_radiotap_he_mu {int /*<<< orphan*/  flags2; int /*<<< orphan*/  flags1; } ;
struct ieee80211_radiotap_he {int /*<<< orphan*/  data3; int /*<<< orphan*/  data1; int /*<<< orphan*/  data4; int /*<<< orphan*/  data6; int /*<<< orphan*/  data5; int /*<<< orphan*/  data2; } ;

/* Variables and functions */
 int IEEE80211_RADIOTAP_HE_DATA1_BEAM_CHANGE_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA1_BSS_COLOR_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA1_DOPPLER_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA1_LDPC_XSYMSEG_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE2_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE3_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE4_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA1_UL_DL_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA2_NUM_LTF_SYMS_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA2_PE_DISAMBIG_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA2_PRE_FEC_PAD_KNOWN ; 
 int IEEE80211_RADIOTAP_HE_DATA2_TXOP_KNOWN ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA3_BEAM_CHANGE ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA3_BSS_COLOR ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA3_LDPC_XSYMSEG ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA3_UL_DL ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA4_SU_MU_SPTL_REUSE ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE1 ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE2 ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE3 ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE4 ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA5_NUM_LTF_SYMS ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA5_PE_DISAMBIG ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA5_PRE_FEC_PAD ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA6_DOPPLER ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_DATA6_TXOP ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_DCM ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_MCS ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_MU_FLAGS2_PUNC_FROM_SIG_A_BW ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_MU_FLAGS2_SIG_B_COMP ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_HE_MU_FLAGS2_SIG_B_SYMS_USERS ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA0_HE_BEAM_CHNG ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA0_HE_BSS_COLOR_MASK ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA0_HE_DOPPLER ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA0_HE_LDPC_EXT_SYM ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA0_HE_PE_DISAMBIG ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA0_HE_PRE_FEC_PAD_MASK ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA0_HE_SPATIAL_REUSE_MASK ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA0_HE_TXOP_DUR_MASK ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA0_HE_UPLINK ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA1_HE_LTF_NUM_MASK ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA1_HE_MU_SIBG_SYM_OR_USER_NUM_MASK ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA1_HE_MU_SIGB_COMPRESSION ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE1 ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE2 ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE3 ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE4 ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA4_HE_MU_EXT_PREAMBLE_PUNC_TYPE_MASK ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA4_HE_MU_EXT_SIGB_DCM ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA4_HE_MU_EXT_SIGB_MCS_MASK ; 
#define  IWL_RX_PHY_INFO_TYPE_CCK 138 
#define  IWL_RX_PHY_INFO_TYPE_HE_MU 137 
#define  IWL_RX_PHY_INFO_TYPE_HE_MU_EXT 136 
#define  IWL_RX_PHY_INFO_TYPE_HE_SU 135 
#define  IWL_RX_PHY_INFO_TYPE_HE_TB 134 
#define  IWL_RX_PHY_INFO_TYPE_HE_TB_EXT 133 
#define  IWL_RX_PHY_INFO_TYPE_HT 132 
#define  IWL_RX_PHY_INFO_TYPE_NONE 131 
#define  IWL_RX_PHY_INFO_TYPE_OFDM_LGCY 130 
#define  IWL_RX_PHY_INFO_TYPE_VHT_MU 129 
#define  IWL_RX_PHY_INFO_TYPE_VHT_SU 128 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  iwl_mvm_decode_he_mu_ext (struct iwl_mvm*,struct iwl_mvm_rx_phy_data*,int /*<<< orphan*/ ,struct ieee80211_radiotap_he_mu*) ; 
 int /*<<< orphan*/  iwl_mvm_decode_he_phy_ru_alloc (struct iwl_mvm_rx_phy_data*,int /*<<< orphan*/ ,struct ieee80211_radiotap_he*,struct ieee80211_radiotap_he_mu*,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  le16_encode_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_decode_he_phy_data(struct iwl_mvm *mvm,
				       struct iwl_mvm_rx_phy_data *phy_data,
				       struct ieee80211_radiotap_he *he,
				       struct ieee80211_radiotap_he_mu *he_mu,
				       struct ieee80211_rx_status *rx_status,
				       u32 rate_n_flags, int queue)
{
	switch (phy_data->info_type) {
	case IWL_RX_PHY_INFO_TYPE_NONE:
	case IWL_RX_PHY_INFO_TYPE_CCK:
	case IWL_RX_PHY_INFO_TYPE_OFDM_LGCY:
	case IWL_RX_PHY_INFO_TYPE_HT:
	case IWL_RX_PHY_INFO_TYPE_VHT_SU:
	case IWL_RX_PHY_INFO_TYPE_VHT_MU:
		return;
	case IWL_RX_PHY_INFO_TYPE_HE_TB_EXT:
		he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE2_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE3_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE4_KNOWN);
		he->data4 |= le16_encode_bits(le32_get_bits(phy_data->d2,
							    IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE1),
					      IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE1);
		he->data4 |= le16_encode_bits(le32_get_bits(phy_data->d2,
							    IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE2),
					      IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE2);
		he->data4 |= le16_encode_bits(le32_get_bits(phy_data->d2,
							    IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE3),
					      IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE3);
		he->data4 |= le16_encode_bits(le32_get_bits(phy_data->d2,
							    IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE4),
					      IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE4);
		/* fall through */
	case IWL_RX_PHY_INFO_TYPE_HE_SU:
	case IWL_RX_PHY_INFO_TYPE_HE_MU:
	case IWL_RX_PHY_INFO_TYPE_HE_MU_EXT:
	case IWL_RX_PHY_INFO_TYPE_HE_TB:
		/* HE common */
		he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_LDPC_XSYMSEG_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA1_DOPPLER_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA1_BSS_COLOR_KNOWN);
		he->data2 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA2_PRE_FEC_PAD_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA2_PE_DISAMBIG_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA2_TXOP_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA2_NUM_LTF_SYMS_KNOWN);
		he->data3 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_BSS_COLOR_MASK),
					      IEEE80211_RADIOTAP_HE_DATA3_BSS_COLOR);
		if (phy_data->info_type != IWL_RX_PHY_INFO_TYPE_HE_TB &&
		    phy_data->info_type != IWL_RX_PHY_INFO_TYPE_HE_TB_EXT) {
			he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_UL_DL_KNOWN);
			he->data3 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_UPLINK),
						      IEEE80211_RADIOTAP_HE_DATA3_UL_DL);
		}
		he->data3 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_LDPC_EXT_SYM),
					      IEEE80211_RADIOTAP_HE_DATA3_LDPC_XSYMSEG);
		he->data5 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_PRE_FEC_PAD_MASK),
					      IEEE80211_RADIOTAP_HE_DATA5_PRE_FEC_PAD);
		he->data5 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_PE_DISAMBIG),
					      IEEE80211_RADIOTAP_HE_DATA5_PE_DISAMBIG);
		he->data5 |= le16_encode_bits(le32_get_bits(phy_data->d1,
							    IWL_RX_PHY_DATA1_HE_LTF_NUM_MASK),
					      IEEE80211_RADIOTAP_HE_DATA5_NUM_LTF_SYMS);
		he->data6 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_TXOP_DUR_MASK),
					      IEEE80211_RADIOTAP_HE_DATA6_TXOP);
		he->data6 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_DOPPLER),
					      IEEE80211_RADIOTAP_HE_DATA6_DOPPLER);
		break;
	}

	switch (phy_data->info_type) {
	case IWL_RX_PHY_INFO_TYPE_HE_MU_EXT:
	case IWL_RX_PHY_INFO_TYPE_HE_MU:
	case IWL_RX_PHY_INFO_TYPE_HE_SU:
		he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE_KNOWN);
		he->data4 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_SPATIAL_REUSE_MASK),
					      IEEE80211_RADIOTAP_HE_DATA4_SU_MU_SPTL_REUSE);
		break;
	default:
		/* nothing here */
		break;
	}

	switch (phy_data->info_type) {
	case IWL_RX_PHY_INFO_TYPE_HE_MU_EXT:
		he_mu->flags1 |=
			le16_encode_bits(le16_get_bits(phy_data->d4,
						       IWL_RX_PHY_DATA4_HE_MU_EXT_SIGB_DCM),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_DCM);
		he_mu->flags1 |=
			le16_encode_bits(le16_get_bits(phy_data->d4,
						       IWL_RX_PHY_DATA4_HE_MU_EXT_SIGB_MCS_MASK),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_MCS);
		he_mu->flags2 |=
			le16_encode_bits(le16_get_bits(phy_data->d4,
						       IWL_RX_PHY_DATA4_HE_MU_EXT_PREAMBLE_PUNC_TYPE_MASK),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS2_PUNC_FROM_SIG_A_BW);
		iwl_mvm_decode_he_mu_ext(mvm, phy_data, rate_n_flags, he_mu);
		/* fall through */
	case IWL_RX_PHY_INFO_TYPE_HE_MU:
		he_mu->flags2 |=
			le16_encode_bits(le32_get_bits(phy_data->d1,
						       IWL_RX_PHY_DATA1_HE_MU_SIBG_SYM_OR_USER_NUM_MASK),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS2_SIG_B_SYMS_USERS);
		he_mu->flags2 |=
			le16_encode_bits(le32_get_bits(phy_data->d1,
						       IWL_RX_PHY_DATA1_HE_MU_SIGB_COMPRESSION),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS2_SIG_B_COMP);
		/* fall through */
	case IWL_RX_PHY_INFO_TYPE_HE_TB:
	case IWL_RX_PHY_INFO_TYPE_HE_TB_EXT:
		iwl_mvm_decode_he_phy_ru_alloc(phy_data, rate_n_flags,
					       he, he_mu, rx_status);
		break;
	case IWL_RX_PHY_INFO_TYPE_HE_SU:
		he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_BEAM_CHANGE_KNOWN);
		he->data3 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_BEAM_CHNG),
					      IEEE80211_RADIOTAP_HE_DATA3_BEAM_CHANGE);
		break;
	default:
		/* nothing */
		break;
	}
}