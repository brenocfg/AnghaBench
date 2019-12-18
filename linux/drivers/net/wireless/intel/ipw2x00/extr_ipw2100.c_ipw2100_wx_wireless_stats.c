#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int retries; } ;
struct TYPE_5__ {int beacon; } ;
struct TYPE_4__ {int qual; int updated; scalar_t__ noise; void* level; } ;
struct iw_statistics {TYPE_3__ discard; TYPE_2__ miss; TYPE_1__ qual; } ;
struct ipw2100_priv {int status; struct iw_statistics wstats; } ;

/* Variables and functions */
 void* IPW2100_RSSI_TO_DBM ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*) ; 
 int /*<<< orphan*/  IPW_ORD_RSSI_AVG_CURR ; 
 int /*<<< orphan*/  IPW_ORD_STAT_PERCENT_MISSED_BCNS ; 
 int /*<<< orphan*/  IPW_ORD_STAT_PERCENT_RETRIES ; 
 int /*<<< orphan*/  IPW_ORD_STAT_TX_FAILURES ; 
 int IW_QUAL_LEVEL_INVALID ; 
 int IW_QUAL_NOISE_INVALID ; 
 int IW_QUAL_QUAL_INVALID ; 
 int STATUS_ASSOCIATED ; 
 scalar_t__ ipw2100_get_ordinal (struct ipw2100_priv*,int /*<<< orphan*/ ,int*,int*) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int min (int,int) ; 

__attribute__((used)) static struct iw_statistics *ipw2100_wx_wireless_stats(struct net_device *dev)
{
	enum {
		POOR = 30,
		FAIR = 60,
		GOOD = 80,
		VERY_GOOD = 90,
		EXCELLENT = 95,
		PERFECT = 100
	};
	int rssi_qual;
	int tx_qual;
	int beacon_qual;
	int quality;

	struct ipw2100_priv *priv = libipw_priv(dev);
	struct iw_statistics *wstats;
	u32 rssi, tx_retries, missed_beacons, tx_failures;
	u32 ord_len = sizeof(u32);

	if (!priv)
		return (struct iw_statistics *)NULL;

	wstats = &priv->wstats;

	/* if hw is disabled, then ipw2100_get_ordinal() can't be called.
	 * ipw2100_wx_wireless_stats seems to be called before fw is
	 * initialized.  STATUS_ASSOCIATED will only be set if the hw is up
	 * and associated; if not associcated, the values are all meaningless
	 * anyway, so set them all to NULL and INVALID */
	if (!(priv->status & STATUS_ASSOCIATED)) {
		wstats->miss.beacon = 0;
		wstats->discard.retries = 0;
		wstats->qual.qual = 0;
		wstats->qual.level = 0;
		wstats->qual.noise = 0;
		wstats->qual.updated = 7;
		wstats->qual.updated |= IW_QUAL_NOISE_INVALID |
		    IW_QUAL_QUAL_INVALID | IW_QUAL_LEVEL_INVALID;
		return wstats;
	}

	if (ipw2100_get_ordinal(priv, IPW_ORD_STAT_PERCENT_MISSED_BCNS,
				&missed_beacons, &ord_len))
		goto fail_get_ordinal;

	/* If we don't have a connection the quality and level is 0 */
	if (!(priv->status & STATUS_ASSOCIATED)) {
		wstats->qual.qual = 0;
		wstats->qual.level = 0;
	} else {
		if (ipw2100_get_ordinal(priv, IPW_ORD_RSSI_AVG_CURR,
					&rssi, &ord_len))
			goto fail_get_ordinal;
		wstats->qual.level = rssi + IPW2100_RSSI_TO_DBM;
		if (rssi < 10)
			rssi_qual = rssi * POOR / 10;
		else if (rssi < 15)
			rssi_qual = (rssi - 10) * (FAIR - POOR) / 5 + POOR;
		else if (rssi < 20)
			rssi_qual = (rssi - 15) * (GOOD - FAIR) / 5 + FAIR;
		else if (rssi < 30)
			rssi_qual = (rssi - 20) * (VERY_GOOD - GOOD) /
			    10 + GOOD;
		else
			rssi_qual = (rssi - 30) * (PERFECT - VERY_GOOD) /
			    10 + VERY_GOOD;

		if (ipw2100_get_ordinal(priv, IPW_ORD_STAT_PERCENT_RETRIES,
					&tx_retries, &ord_len))
			goto fail_get_ordinal;

		if (tx_retries > 75)
			tx_qual = (90 - tx_retries) * POOR / 15;
		else if (tx_retries > 70)
			tx_qual = (75 - tx_retries) * (FAIR - POOR) / 5 + POOR;
		else if (tx_retries > 65)
			tx_qual = (70 - tx_retries) * (GOOD - FAIR) / 5 + FAIR;
		else if (tx_retries > 50)
			tx_qual = (65 - tx_retries) * (VERY_GOOD - GOOD) /
			    15 + GOOD;
		else
			tx_qual = (50 - tx_retries) *
			    (PERFECT - VERY_GOOD) / 50 + VERY_GOOD;

		if (missed_beacons > 50)
			beacon_qual = (60 - missed_beacons) * POOR / 10;
		else if (missed_beacons > 40)
			beacon_qual = (50 - missed_beacons) * (FAIR - POOR) /
			    10 + POOR;
		else if (missed_beacons > 32)
			beacon_qual = (40 - missed_beacons) * (GOOD - FAIR) /
			    18 + FAIR;
		else if (missed_beacons > 20)
			beacon_qual = (32 - missed_beacons) *
			    (VERY_GOOD - GOOD) / 20 + GOOD;
		else
			beacon_qual = (20 - missed_beacons) *
			    (PERFECT - VERY_GOOD) / 20 + VERY_GOOD;

		quality = min(tx_qual, rssi_qual);
		quality = min(beacon_qual, quality);

#ifdef CONFIG_IPW2100_DEBUG
		if (beacon_qual == quality)
			IPW_DEBUG_WX("Quality clamped by Missed Beacons\n");
		else if (tx_qual == quality)
			IPW_DEBUG_WX("Quality clamped by Tx Retries\n");
		else if (quality != 100)
			IPW_DEBUG_WX("Quality clamped by Signal Strength\n");
		else
			IPW_DEBUG_WX("Quality not clamped.\n");
#endif

		wstats->qual.qual = quality;
		wstats->qual.level = rssi + IPW2100_RSSI_TO_DBM;
	}

	wstats->qual.noise = 0;
	wstats->qual.updated = 7;
	wstats->qual.updated |= IW_QUAL_NOISE_INVALID;

	/* FIXME: this is percent and not a # */
	wstats->miss.beacon = missed_beacons;

	if (ipw2100_get_ordinal(priv, IPW_ORD_STAT_TX_FAILURES,
				&tx_failures, &ord_len))
		goto fail_get_ordinal;
	wstats->discard.retries = tx_failures;

	return wstats;

      fail_get_ordinal:
	IPW_DEBUG_WX("failed querying ordinals.\n");

	return (struct iw_statistics *)NULL;
}