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
struct xgbe_mmc_stats {int /*<<< orphan*/  txvlanframes_g; int /*<<< orphan*/  txpauseframes; int /*<<< orphan*/  txframecount_g; int /*<<< orphan*/  txoctetcount_g; int /*<<< orphan*/  txunderflowerror; int /*<<< orphan*/  txbroadcastframes_g; int /*<<< orphan*/  txmulticastframes_gb; int /*<<< orphan*/  txunicastframes_gb; int /*<<< orphan*/  tx1024tomaxoctets_gb; int /*<<< orphan*/  tx512to1023octets_gb; int /*<<< orphan*/  tx256to511octets_gb; int /*<<< orphan*/  tx128to255octets_gb; int /*<<< orphan*/  tx65to127octets_gb; int /*<<< orphan*/  tx64octets_gb; int /*<<< orphan*/  txmulticastframes_g; int /*<<< orphan*/  txframecount_gb; int /*<<< orphan*/  txoctetcount_gb; } ;
struct xgbe_prv_data {struct xgbe_mmc_stats mmc_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_TISR ; 
 int /*<<< orphan*/  MMC_TX1024TOMAXOCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TX128TO255OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TX256TO511OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TX512TO1023OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TX64OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TX65TO127OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TXBROADCASTFRAMES_GB_LO ; 
 int /*<<< orphan*/  MMC_TXBROADCASTFRAMES_G_LO ; 
 int /*<<< orphan*/  MMC_TXFRAMECOUNT_GB_LO ; 
 int /*<<< orphan*/  MMC_TXFRAMECOUNT_G_LO ; 
 int /*<<< orphan*/  MMC_TXMULTICASTFRAMES_GB_LO ; 
 int /*<<< orphan*/  MMC_TXMULTICASTFRAMES_G_LO ; 
 int /*<<< orphan*/  MMC_TXOCTETCOUNT_GB_LO ; 
 int /*<<< orphan*/  MMC_TXOCTETCOUNT_G_LO ; 
 int /*<<< orphan*/  MMC_TXPAUSEFRAMES_LO ; 
 int /*<<< orphan*/  MMC_TXUNDERFLOWERROR_LO ; 
 int /*<<< orphan*/  MMC_TXUNICASTFRAMES_GB_LO ; 
 int /*<<< orphan*/  MMC_TXVLANFRAMES_G_LO ; 
 int /*<<< orphan*/  TX1024TOMAXOCTETS_GB ; 
 int /*<<< orphan*/  TX128TO255OCTETS_GB ; 
 int /*<<< orphan*/  TX256TO511OCTETS_GB ; 
 int /*<<< orphan*/  TX512TO1023OCTETS_GB ; 
 int /*<<< orphan*/  TX64OCTETS_GB ; 
 int /*<<< orphan*/  TX65TO127OCTETS_GB ; 
 int /*<<< orphan*/  TXBROADCASTFRAMES_G ; 
 int /*<<< orphan*/  TXBROADCASTFRAMES_GB ; 
 int /*<<< orphan*/  TXFRAMECOUNT_G ; 
 int /*<<< orphan*/  TXFRAMECOUNT_GB ; 
 int /*<<< orphan*/  TXMULTICASTFRAMES_G ; 
 int /*<<< orphan*/  TXMULTICASTFRAMES_GB ; 
 int /*<<< orphan*/  TXOCTETCOUNT_G ; 
 int /*<<< orphan*/  TXOCTETCOUNT_GB ; 
 int /*<<< orphan*/  TXPAUSEFRAMES ; 
 int /*<<< orphan*/  TXUNDERFLOWERROR ; 
 int /*<<< orphan*/  TXUNICASTFRAMES_GB ; 
 int /*<<< orphan*/  TXVLANFRAMES_G ; 
 scalar_t__ XGMAC_GET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int XGMAC_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ xgbe_mmc_read (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_tx_mmc_int(struct xgbe_prv_data *pdata)
{
	struct xgbe_mmc_stats *stats = &pdata->mmc_stats;
	unsigned int mmc_isr = XGMAC_IOREAD(pdata, MMC_TISR);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXOCTETCOUNT_GB))
		stats->txoctetcount_gb +=
			xgbe_mmc_read(pdata, MMC_TXOCTETCOUNT_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXFRAMECOUNT_GB))
		stats->txframecount_gb +=
			xgbe_mmc_read(pdata, MMC_TXFRAMECOUNT_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXBROADCASTFRAMES_G))
		stats->txbroadcastframes_g +=
			xgbe_mmc_read(pdata, MMC_TXBROADCASTFRAMES_G_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXMULTICASTFRAMES_G))
		stats->txmulticastframes_g +=
			xgbe_mmc_read(pdata, MMC_TXMULTICASTFRAMES_G_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX64OCTETS_GB))
		stats->tx64octets_gb +=
			xgbe_mmc_read(pdata, MMC_TX64OCTETS_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX65TO127OCTETS_GB))
		stats->tx65to127octets_gb +=
			xgbe_mmc_read(pdata, MMC_TX65TO127OCTETS_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX128TO255OCTETS_GB))
		stats->tx128to255octets_gb +=
			xgbe_mmc_read(pdata, MMC_TX128TO255OCTETS_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX256TO511OCTETS_GB))
		stats->tx256to511octets_gb +=
			xgbe_mmc_read(pdata, MMC_TX256TO511OCTETS_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX512TO1023OCTETS_GB))
		stats->tx512to1023octets_gb +=
			xgbe_mmc_read(pdata, MMC_TX512TO1023OCTETS_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX1024TOMAXOCTETS_GB))
		stats->tx1024tomaxoctets_gb +=
			xgbe_mmc_read(pdata, MMC_TX1024TOMAXOCTETS_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXUNICASTFRAMES_GB))
		stats->txunicastframes_gb +=
			xgbe_mmc_read(pdata, MMC_TXUNICASTFRAMES_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXMULTICASTFRAMES_GB))
		stats->txmulticastframes_gb +=
			xgbe_mmc_read(pdata, MMC_TXMULTICASTFRAMES_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXBROADCASTFRAMES_GB))
		stats->txbroadcastframes_g +=
			xgbe_mmc_read(pdata, MMC_TXBROADCASTFRAMES_GB_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXUNDERFLOWERROR))
		stats->txunderflowerror +=
			xgbe_mmc_read(pdata, MMC_TXUNDERFLOWERROR_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXOCTETCOUNT_G))
		stats->txoctetcount_g +=
			xgbe_mmc_read(pdata, MMC_TXOCTETCOUNT_G_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXFRAMECOUNT_G))
		stats->txframecount_g +=
			xgbe_mmc_read(pdata, MMC_TXFRAMECOUNT_G_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXPAUSEFRAMES))
		stats->txpauseframes +=
			xgbe_mmc_read(pdata, MMC_TXPAUSEFRAMES_LO);

	if (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXVLANFRAMES_G))
		stats->txvlanframes_g +=
			xgbe_mmc_read(pdata, MMC_TXVLANFRAMES_G_LO);
}