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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtl_80211_hdr_3addr {int /*<<< orphan*/  seq_ctl; } ;
struct TYPE_4__ {size_t* slide_signal_strength; size_t slide_rssi_total; int* rx_rssi_percentage; size_t* Slide_Beacon_pwdb; size_t Slide_Beacon_Total; size_t* slide_evm; size_t slide_evm_total; size_t signal_quality; size_t last_signal_strength_inpercent; int* rx_evm_percentage; int /*<<< orphan*/  num_process_phyinfo; int /*<<< orphan*/  signal_strength; } ;
struct r8192_priv {size_t NumTotalRFPath; int undecorated_smoothed_pwdb; TYPE_2__ stats; TYPE_1__* ieee80211; } ;
struct ieee80211_rx_stats {unsigned int Seq_Num; size_t SignalStrength; int* RxMIMOSignalStrength; size_t RxPWDBAll; size_t SignalQuality; int* RxMIMOSignalQuality; scalar_t__ bToSelfBA; scalar_t__ bPacketBeacon; scalar_t__ bPacketToSelf; scalar_t__ bIsCCK; int /*<<< orphan*/  bPacketMatchBSSID; int /*<<< orphan*/  rssi; int /*<<< orphan*/  bIsAMPDU; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DBG ; 
 int /*<<< orphan*/  COMP_RXDESC ; 
 size_t PHY_Beacon_RSSI_SLID_WIN_MAX ; 
 size_t PHY_RSSI_SLID_WIN_MAX ; 
 size_t RF90_PATH_A ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int RX_SMOOTH_FACTOR ; 
 unsigned int WLAN_GET_SEQ_SEQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_phy_CheckIsLegalRFPath (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  rtl819x_translate_todbm (size_t) ; 

__attribute__((used)) static void rtl8192_process_phyinfo(struct r8192_priv *priv, u8 *buffer,
				    struct ieee80211_rx_stats *pprevious_stats,
				    struct ieee80211_rx_stats *pcurrent_stats)
{
	bool bcheck = false;
	u8	rfpath;
	u32	nspatial_stream, tmp_val;
	static u32 slide_rssi_index, slide_rssi_statistics;
	static u32 slide_evm_index, slide_evm_statistics;
	static u32 last_rssi, last_evm;

	static u32 slide_beacon_adc_pwdb_index;
	static u32 slide_beacon_adc_pwdb_statistics;
	static u32 last_beacon_adc_pwdb;

	struct rtl_80211_hdr_3addr *hdr;
	u16 sc;
	unsigned int seq;

	hdr = (struct rtl_80211_hdr_3addr *)buffer;
	sc = le16_to_cpu(hdr->seq_ctl);
	seq = WLAN_GET_SEQ_SEQ(sc);
	/* to record the sequence number */
	pcurrent_stats->Seq_Num = seq;

	/* Check whether we should take the previous packet into accounting */
	if (!pprevious_stats->bIsAMPDU) {
		/* if previous packet is not aggregated packet */
		bcheck = true;
	}

	if (slide_rssi_statistics++ >= PHY_RSSI_SLID_WIN_MAX) {
		slide_rssi_statistics = PHY_RSSI_SLID_WIN_MAX;
		last_rssi = priv->stats.slide_signal_strength[slide_rssi_index];
		priv->stats.slide_rssi_total -= last_rssi;
	}
	priv->stats.slide_rssi_total += pprevious_stats->SignalStrength;

	priv->stats.slide_signal_strength[slide_rssi_index++] =
		pprevious_stats->SignalStrength;
	if (slide_rssi_index >= PHY_RSSI_SLID_WIN_MAX)
		slide_rssi_index = 0;

	/* <1> Showed on UI for user, in dbm */
	tmp_val = priv->stats.slide_rssi_total / slide_rssi_statistics;
	priv->stats.signal_strength = rtl819x_translate_todbm((u8)tmp_val);
	pcurrent_stats->rssi = priv->stats.signal_strength;

	/* If the previous packet does not match the criteria, neglect it */
	if (!pprevious_stats->bPacketMatchBSSID) {
		if (!pprevious_stats->bToSelfBA)
			return;
	}

	if (!bcheck)
		return;


	/* only rtl8190 supported
	 * rtl8190_process_cck_rxpathsel(priv,pprevious_stats);
	 */

	/* Check RSSI */
	priv->stats.num_process_phyinfo++;

	/* record the general signal strength to the sliding window. */


	/* <2> Showed on UI for engineering
	 * hardware does not provide rssi information for each rf path in CCK
	 */
	if (!pprevious_stats->bIsCCK &&
	    (pprevious_stats->bPacketToSelf || pprevious_stats->bToSelfBA)) {
		for (rfpath = RF90_PATH_A; rfpath < priv->NumTotalRFPath; rfpath++) {
			if (!rtl8192_phy_CheckIsLegalRFPath(
					priv->ieee80211->dev, rfpath))
				continue;

			if (priv->stats.rx_rssi_percentage[rfpath] == 0)
				priv->stats.rx_rssi_percentage[rfpath] =
					pprevious_stats->RxMIMOSignalStrength[rfpath];
			if (pprevious_stats->RxMIMOSignalStrength[rfpath]  > priv->stats.rx_rssi_percentage[rfpath]) {
				priv->stats.rx_rssi_percentage[rfpath] =
					((priv->stats.rx_rssi_percentage[rfpath] * (RX_SMOOTH_FACTOR - 1)) +
					 (pprevious_stats->RxMIMOSignalStrength[rfpath])) / (RX_SMOOTH_FACTOR);
				priv->stats.rx_rssi_percentage[rfpath] = priv->stats.rx_rssi_percentage[rfpath]  + 1;
			} else {
				priv->stats.rx_rssi_percentage[rfpath] =
					((priv->stats.rx_rssi_percentage[rfpath] * (RX_SMOOTH_FACTOR - 1)) +
					 (pprevious_stats->RxMIMOSignalStrength[rfpath])) / (RX_SMOOTH_FACTOR);
			}
			RT_TRACE(COMP_DBG,
				 "priv->stats.rx_rssi_percentage[rfPath]  = %d\n",
				 priv->stats.rx_rssi_percentage[rfpath]);
		}
	}


	/* Check PWDB. */
	RT_TRACE(COMP_RXDESC, "Smooth %s PWDB = %d\n",
		 pprevious_stats->bIsCCK ? "CCK" : "OFDM",
		 pprevious_stats->RxPWDBAll);

	if (pprevious_stats->bPacketBeacon) {
		/* record the beacon pwdb to the sliding window. */
		if (slide_beacon_adc_pwdb_statistics++ >= PHY_Beacon_RSSI_SLID_WIN_MAX) {
			slide_beacon_adc_pwdb_statistics = PHY_Beacon_RSSI_SLID_WIN_MAX;
			last_beacon_adc_pwdb = priv->stats.Slide_Beacon_pwdb[slide_beacon_adc_pwdb_index];
			priv->stats.Slide_Beacon_Total -= last_beacon_adc_pwdb;
		}
		priv->stats.Slide_Beacon_Total += pprevious_stats->RxPWDBAll;
		priv->stats.Slide_Beacon_pwdb[slide_beacon_adc_pwdb_index] = pprevious_stats->RxPWDBAll;
		slide_beacon_adc_pwdb_index++;
		if (slide_beacon_adc_pwdb_index >= PHY_Beacon_RSSI_SLID_WIN_MAX)
			slide_beacon_adc_pwdb_index = 0;
		pprevious_stats->RxPWDBAll = priv->stats.Slide_Beacon_Total / slide_beacon_adc_pwdb_statistics;
		if (pprevious_stats->RxPWDBAll >= 3)
			pprevious_stats->RxPWDBAll -= 3;
	}

	RT_TRACE(COMP_RXDESC, "Smooth %s PWDB = %d\n",
		 pprevious_stats->bIsCCK ? "CCK" : "OFDM",
		 pprevious_stats->RxPWDBAll);


	if (pprevious_stats->bPacketToSelf ||
	    pprevious_stats->bPacketBeacon ||
	    pprevious_stats->bToSelfBA) {
		if (priv->undecorated_smoothed_pwdb < 0)
			/* initialize */
			priv->undecorated_smoothed_pwdb =
				pprevious_stats->RxPWDBAll;
		if (pprevious_stats->RxPWDBAll > (u32)priv->undecorated_smoothed_pwdb) {
			priv->undecorated_smoothed_pwdb =
				(((priv->undecorated_smoothed_pwdb) * (RX_SMOOTH_FACTOR - 1)) +
				 (pprevious_stats->RxPWDBAll)) / (RX_SMOOTH_FACTOR);
			priv->undecorated_smoothed_pwdb = priv->undecorated_smoothed_pwdb + 1;
		} else {
			priv->undecorated_smoothed_pwdb =
				(((priv->undecorated_smoothed_pwdb) * (RX_SMOOTH_FACTOR - 1)) +
				 (pprevious_stats->RxPWDBAll)) / (RX_SMOOTH_FACTOR);
		}
	}

	/* Check EVM */
	/* record the general EVM to the sliding window. */
	if (pprevious_stats->SignalQuality) {
		if (pprevious_stats->bPacketToSelf ||
		    pprevious_stats->bPacketBeacon ||
		    pprevious_stats->bToSelfBA) {
			if (slide_evm_statistics++ >= PHY_RSSI_SLID_WIN_MAX) {
				slide_evm_statistics = PHY_RSSI_SLID_WIN_MAX;
				last_evm = priv->stats.slide_evm[slide_evm_index];
				priv->stats.slide_evm_total -= last_evm;
			}

			priv->stats.slide_evm_total +=
				pprevious_stats->SignalQuality;

			priv->stats.slide_evm[slide_evm_index++] =
				pprevious_stats->SignalQuality;
			if (slide_evm_index >= PHY_RSSI_SLID_WIN_MAX)
				slide_evm_index = 0;

			/* <1> Showed on UI for user, in percentage. */
			tmp_val = priv->stats.slide_evm_total /
				  slide_evm_statistics;
			priv->stats.signal_quality = tmp_val;
			/* Showed on UI for user in Windows Vista,
			 * for Link quality.
			 */
			priv->stats.last_signal_strength_inpercent = tmp_val;
		}

		/* <2> Showed on UI for engineering */
		if (pprevious_stats->bPacketToSelf ||
		    pprevious_stats->bPacketBeacon ||
		    pprevious_stats->bToSelfBA) {
			for (nspatial_stream = 0; nspatial_stream < 2; nspatial_stream++) { /* 2 spatial stream */
				if (pprevious_stats->RxMIMOSignalQuality[nspatial_stream] != -1) {
					if (priv->stats.rx_evm_percentage[nspatial_stream] == 0) /* initialize */
						priv->stats.rx_evm_percentage[nspatial_stream] = pprevious_stats->RxMIMOSignalQuality[nspatial_stream];
					priv->stats.rx_evm_percentage[nspatial_stream] =
						((priv->stats.rx_evm_percentage[nspatial_stream] * (RX_SMOOTH_FACTOR - 1)) +
						 (pprevious_stats->RxMIMOSignalQuality[nspatial_stream] * 1)) / (RX_SMOOTH_FACTOR);
				}
			}
		}
	}
}