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
typedef  int u32 ;
struct TYPE_2__ {int legacy; } ;
struct station_info {int filled; int signal; void* tx_failed; void* tx_packets; void* rx_dropped_misc; void* rx_packets; TYPE_1__ txrate; } ;
struct brcmf_scb_val_le {int /*<<< orphan*/  tx_bad_pkt; int /*<<< orphan*/  tx_good_pkt; int /*<<< orphan*/  rx_bad_pkt; int /*<<< orphan*/  rx_good_pkt; int /*<<< orphan*/  val; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_pktcnt_le {int /*<<< orphan*/  tx_bad_pkt; int /*<<< orphan*/  tx_good_pkt; int /*<<< orphan*/  rx_bad_pkt; int /*<<< orphan*/  rx_good_pkt; int /*<<< orphan*/  val; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
typedef  int /*<<< orphan*/  scbval ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  pktcnt ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRCMF_C_GET_GET_PKTCNTS ; 
 int /*<<< orphan*/  BRCMF_C_GET_RATE ; 
 int /*<<< orphan*/  BRCMF_C_GET_RSSI ; 
 int /*<<< orphan*/  NL80211_STA_INFO_RX_DROP_MISC ; 
 int /*<<< orphan*/  NL80211_STA_INFO_RX_PACKETS ; 
 int /*<<< orphan*/  NL80211_STA_INFO_SIGNAL ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_BITRATE ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_FAILED ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_PACKETS ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,scalar_t__) ; 
 scalar_t__ brcmf_fil_cmd_data_get (struct brcmf_if*,int /*<<< orphan*/ ,struct brcmf_scb_val_le*,int) ; 
 scalar_t__ brcmf_fil_cmd_int_get (struct brcmf_if*,int /*<<< orphan*/ ,int*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct brcmf_scb_val_le*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32
brcmf_cfg80211_get_station_ibss(struct brcmf_if *ifp,
				struct station_info *sinfo)
{
	struct brcmf_pub *drvr = ifp->drvr;
	struct brcmf_scb_val_le scbval;
	struct brcmf_pktcnt_le pktcnt;
	s32 err;
	u32 rate;
	u32 rssi;

	/* Get the current tx rate */
	err = brcmf_fil_cmd_int_get(ifp, BRCMF_C_GET_RATE, &rate);
	if (err < 0) {
		bphy_err(drvr, "BRCMF_C_GET_RATE error (%d)\n", err);
		return err;
	}
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
	sinfo->txrate.legacy = rate * 5;

	memset(&scbval, 0, sizeof(scbval));
	err = brcmf_fil_cmd_data_get(ifp, BRCMF_C_GET_RSSI, &scbval,
				     sizeof(scbval));
	if (err) {
		bphy_err(drvr, "BRCMF_C_GET_RSSI error (%d)\n", err);
		return err;
	}
	rssi = le32_to_cpu(scbval.val);
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
	sinfo->signal = rssi;

	err = brcmf_fil_cmd_data_get(ifp, BRCMF_C_GET_GET_PKTCNTS, &pktcnt,
				     sizeof(pktcnt));
	if (err) {
		bphy_err(drvr, "BRCMF_C_GET_GET_PKTCNTS error (%d)\n", err);
		return err;
	}
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_PACKETS) |
			 BIT_ULL(NL80211_STA_INFO_RX_DROP_MISC) |
			 BIT_ULL(NL80211_STA_INFO_TX_PACKETS) |
			 BIT_ULL(NL80211_STA_INFO_TX_FAILED);
	sinfo->rx_packets = le32_to_cpu(pktcnt.rx_good_pkt);
	sinfo->rx_dropped_misc = le32_to_cpu(pktcnt.rx_bad_pkt);
	sinfo->tx_packets = le32_to_cpu(pktcnt.tx_good_pkt);
	sinfo->tx_failed  = le32_to_cpu(pktcnt.tx_bad_pkt);

	return 0;
}