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
typedef  int u8 ;
struct sk_buff {scalar_t__ data; scalar_t__ cb; } ;
struct rx_drvinfo_819x_usb {int PartAggr; int FirstAGGR; int /*<<< orphan*/  BW; int /*<<< orphan*/  TSFL; int /*<<< orphan*/  SPLCP; int /*<<< orphan*/  RxRate; int /*<<< orphan*/  RxHT; } ;
struct rx_desc_819x_usb {int Length; int ICV; int CRC32; int /*<<< orphan*/  SWDec; int /*<<< orphan*/  RxDrvInfoSize; } ;
struct rtl8192_rx_info {struct net_device* dev; } ;
struct r8192_priv {TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_rx_stats {int Length; int bICV; int bCRC; int bHwError; int Decrypted; int rate; int bIsAMPDU; int bFirstMPDU; int bShift; int /*<<< orphan*/  RxIs40MHzPacket; int /*<<< orphan*/  RxDrvInfoSize; int /*<<< orphan*/  RxBufShift; int /*<<< orphan*/  TimeStampLow; int /*<<< orphan*/  bShortPreamble; } ;
struct TYPE_4__ {scalar_t__ pairwise_key_type; TYPE_1__* pHTInfo; } ;
struct TYPE_3__ {scalar_t__ bCurrentHTSupport; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RXDESC ; 
 int HwRateToMRate90 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KEY_TYPE_CCMP ; 
 int MAX_8192U_RX_SIZE ; 
 int MGN_1M ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  TranslateRxSignalStuff819xUsb (struct sk_buff*,struct ieee80211_rx_stats*,struct rx_drvinfo_819x_usb*) ; 
 int /*<<< orphan*/  UpdateReceivedRateHistogramStatistics8190 (struct net_device*,struct ieee80211_rx_stats*) ; 
 int /*<<< orphan*/  UpdateRxPktTimeStamp8190 (struct net_device*,struct ieee80211_rx_stats*) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void query_rxdesc_status(struct sk_buff *skb,
				struct ieee80211_rx_stats *stats,
				bool bIsRxAggrSubframe)
{
	struct rtl8192_rx_info *info = (struct rtl8192_rx_info *)skb->cb;
	struct net_device *dev = info->dev;
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	struct rx_drvinfo_819x_usb  *driver_info = NULL;

	/* Get Rx Descriptor Information */
	struct rx_desc_819x_usb *desc = (struct rx_desc_819x_usb *)skb->data;

	stats->Length = desc->Length;
	stats->RxDrvInfoSize = desc->RxDrvInfoSize;
	stats->RxBufShift = 0;
	stats->bICV = desc->ICV;
	stats->bCRC = desc->CRC32;
	stats->bHwError = stats->bCRC | stats->bICV;
	/* RTL8190 set this bit to indicate that Hw does not decrypt packet */
	stats->Decrypted = !desc->SWDec;

	if ((priv->ieee80211->pHTInfo->bCurrentHTSupport) &&
	    (priv->ieee80211->pairwise_key_type == KEY_TYPE_CCMP))
		stats->bHwError = false;
	else
		stats->bHwError = stats->bCRC | stats->bICV;

	if (stats->Length < 24 || stats->Length > MAX_8192U_RX_SIZE)
		stats->bHwError |= 1;
	/* Get Driver Info */
	/* TODO: Need to verify it on FGPA platform
	 * Driver info are written to the RxBuffer following rx desc
	 */
	if (stats->RxDrvInfoSize != 0) {
		driver_info = (struct rx_drvinfo_819x_usb *)(
				skb->data
				+ sizeof(struct rx_desc_819x_usb)
				+ stats->RxBufShift
			      );
		/* unit: 0.5M */
		/* TODO */
		if (!stats->bHwError) {
			u8	ret_rate;

			ret_rate = HwRateToMRate90(driver_info->RxHT,
						   driver_info->RxRate);
			if (ret_rate == 0xff) {
				/* Abnormal Case: Receive CRC OK packet with Rx
				 * descriptor indicating non supported rate.
				 * Special Error Handling here
				 */

				stats->bHwError = 1;
				/* Set 1M rate by default */
				stats->rate = MGN_1M;
			} else {
				stats->rate = ret_rate;
			}
		} else {
			stats->rate = 0x02;
		}

		stats->bShortPreamble = driver_info->SPLCP;


		UpdateReceivedRateHistogramStatistics8190(dev, stats);

		stats->bIsAMPDU = (driver_info->PartAggr == 1);
		stats->bFirstMPDU = (driver_info->PartAggr == 1) &&
				    (driver_info->FirstAGGR == 1);
		stats->TimeStampLow = driver_info->TSFL;

		UpdateRxPktTimeStamp8190(dev, stats);

		/* Rx A-MPDU */
		if (driver_info->FirstAGGR == 1 || driver_info->PartAggr == 1)
			RT_TRACE(COMP_RXDESC,
				"driver_info->FirstAGGR = %d, driver_info->PartAggr = %d\n",
				 driver_info->FirstAGGR, driver_info->PartAggr);
	}

	skb_pull(skb, sizeof(struct rx_desc_819x_usb));
	/* Get Total offset of MPDU Frame Body */
	if ((stats->RxBufShift + stats->RxDrvInfoSize) > 0) {
		stats->bShift = 1;
		skb_pull(skb, stats->RxBufShift + stats->RxDrvInfoSize);
	}

	if (driver_info) {
		stats->RxIs40MHzPacket = driver_info->BW;
		TranslateRxSignalStuff819xUsb(skb, stats, driver_info);
	}
}