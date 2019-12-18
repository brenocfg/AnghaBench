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
struct xlgmac_stats {int /*<<< orphan*/  rxwatchdogerror; int /*<<< orphan*/  rxvlanframes_gb; int /*<<< orphan*/  rxfifooverflow; int /*<<< orphan*/  rxpauseframes; int /*<<< orphan*/  rxoutofrangetype; int /*<<< orphan*/  rxlengtherror; int /*<<< orphan*/  rxunicastframes_g; int /*<<< orphan*/  rx1024tomaxoctets_gb; int /*<<< orphan*/  rx512to1023octets_gb; int /*<<< orphan*/  rx256to511octets_gb; int /*<<< orphan*/  rx128to255octets_gb; int /*<<< orphan*/  rx65to127octets_gb; int /*<<< orphan*/  rx64octets_gb; int /*<<< orphan*/  rxoversize_g; int /*<<< orphan*/  rxundersize_g; int /*<<< orphan*/  rxjabbererror; int /*<<< orphan*/  rxrunterror; int /*<<< orphan*/  rxcrcerror; int /*<<< orphan*/  rxmulticastframes_g; int /*<<< orphan*/  rxbroadcastframes_g; int /*<<< orphan*/  rxoctetcount_g; int /*<<< orphan*/  rxoctetcount_gb; int /*<<< orphan*/  rxframecount_gb; } ;
struct xlgmac_pdata {struct xlgmac_stats stats; scalar_t__ mac_regs; } ;

/* Variables and functions */
 scalar_t__ MMC_RISR ; 
 int /*<<< orphan*/  MMC_RISR_RX1024TOMAXOCTETS_GB_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RX1024TOMAXOCTETS_GB_POS ; 
 int /*<<< orphan*/  MMC_RISR_RX128TO255OCTETS_GB_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RX128TO255OCTETS_GB_POS ; 
 int /*<<< orphan*/  MMC_RISR_RX256TO511OCTETS_GB_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RX256TO511OCTETS_GB_POS ; 
 int /*<<< orphan*/  MMC_RISR_RX512TO1023OCTETS_GB_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RX512TO1023OCTETS_GB_POS ; 
 int /*<<< orphan*/  MMC_RISR_RX64OCTETS_GB_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RX64OCTETS_GB_POS ; 
 int /*<<< orphan*/  MMC_RISR_RX65TO127OCTETS_GB_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RX65TO127OCTETS_GB_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXBROADCASTFRAMES_G_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXBROADCASTFRAMES_G_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXCRCERROR_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXCRCERROR_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXFIFOOVERFLOW_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXFIFOOVERFLOW_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXFRAMECOUNT_GB_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXFRAMECOUNT_GB_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXJABBERERROR_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXJABBERERROR_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXLENGTHERROR_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXLENGTHERROR_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXMULTICASTFRAMES_G_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXMULTICASTFRAMES_G_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXOCTETCOUNT_GB_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXOCTETCOUNT_GB_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXOCTETCOUNT_G_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXOCTETCOUNT_G_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXOUTOFRANGETYPE_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXOUTOFRANGETYPE_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXOVERSIZE_G_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXOVERSIZE_G_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXPAUSEFRAMES_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXPAUSEFRAMES_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXRUNTERROR_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXRUNTERROR_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXUNDERSIZE_G_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXUNDERSIZE_G_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXUNICASTFRAMES_G_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXUNICASTFRAMES_G_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXVLANFRAMES_GB_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXVLANFRAMES_GB_POS ; 
 int /*<<< orphan*/  MMC_RISR_RXWATCHDOGERROR_LEN ; 
 int /*<<< orphan*/  MMC_RISR_RXWATCHDOGERROR_POS ; 
 int /*<<< orphan*/  MMC_RX1024TOMAXOCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RX128TO255OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RX256TO511OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RX512TO1023OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RX64OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RX65TO127OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RXBROADCASTFRAMES_G_LO ; 
 int /*<<< orphan*/  MMC_RXCRCERROR_LO ; 
 int /*<<< orphan*/  MMC_RXFIFOOVERFLOW_LO ; 
 int /*<<< orphan*/  MMC_RXFRAMECOUNT_GB_LO ; 
 int /*<<< orphan*/  MMC_RXJABBERERROR ; 
 int /*<<< orphan*/  MMC_RXLENGTHERROR_LO ; 
 int /*<<< orphan*/  MMC_RXMULTICASTFRAMES_G_LO ; 
 int /*<<< orphan*/  MMC_RXOCTETCOUNT_GB_LO ; 
 int /*<<< orphan*/  MMC_RXOCTETCOUNT_G_LO ; 
 int /*<<< orphan*/  MMC_RXOUTOFRANGETYPE_LO ; 
 int /*<<< orphan*/  MMC_RXOVERSIZE_G ; 
 int /*<<< orphan*/  MMC_RXPAUSEFRAMES_LO ; 
 int /*<<< orphan*/  MMC_RXRUNTERROR ; 
 int /*<<< orphan*/  MMC_RXUNDERSIZE_G ; 
 int /*<<< orphan*/  MMC_RXUNICASTFRAMES_G_LO ; 
 int /*<<< orphan*/  MMC_RXVLANFRAMES_GB_LO ; 
 int /*<<< orphan*/  MMC_RXWATCHDOGERROR ; 
 scalar_t__ XLGMAC_GET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 scalar_t__ xlgmac_mmc_read (struct xlgmac_pdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlgmac_rx_mmc_int(struct xlgmac_pdata *pdata)
{
	unsigned int mmc_isr = readl(pdata->mac_regs + MMC_RISR);
	struct xlgmac_stats *stats = &pdata->stats;

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXFRAMECOUNT_GB_POS,
				MMC_RISR_RXFRAMECOUNT_GB_LEN))
		stats->rxframecount_gb +=
			xlgmac_mmc_read(pdata, MMC_RXFRAMECOUNT_GB_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXOCTETCOUNT_GB_POS,
				MMC_RISR_RXOCTETCOUNT_GB_LEN))
		stats->rxoctetcount_gb +=
			xlgmac_mmc_read(pdata, MMC_RXOCTETCOUNT_GB_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXOCTETCOUNT_G_POS,
				MMC_RISR_RXOCTETCOUNT_G_LEN))
		stats->rxoctetcount_g +=
			xlgmac_mmc_read(pdata, MMC_RXOCTETCOUNT_G_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXBROADCASTFRAMES_G_POS,
				MMC_RISR_RXBROADCASTFRAMES_G_LEN))
		stats->rxbroadcastframes_g +=
			xlgmac_mmc_read(pdata, MMC_RXBROADCASTFRAMES_G_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXMULTICASTFRAMES_G_POS,
				MMC_RISR_RXMULTICASTFRAMES_G_LEN))
		stats->rxmulticastframes_g +=
			xlgmac_mmc_read(pdata, MMC_RXMULTICASTFRAMES_G_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXCRCERROR_POS,
				MMC_RISR_RXCRCERROR_LEN))
		stats->rxcrcerror +=
			xlgmac_mmc_read(pdata, MMC_RXCRCERROR_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXRUNTERROR_POS,
				MMC_RISR_RXRUNTERROR_LEN))
		stats->rxrunterror +=
			xlgmac_mmc_read(pdata, MMC_RXRUNTERROR);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXJABBERERROR_POS,
				MMC_RISR_RXJABBERERROR_LEN))
		stats->rxjabbererror +=
			xlgmac_mmc_read(pdata, MMC_RXJABBERERROR);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXUNDERSIZE_G_POS,
				MMC_RISR_RXUNDERSIZE_G_LEN))
		stats->rxundersize_g +=
			xlgmac_mmc_read(pdata, MMC_RXUNDERSIZE_G);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXOVERSIZE_G_POS,
				MMC_RISR_RXOVERSIZE_G_LEN))
		stats->rxoversize_g +=
			xlgmac_mmc_read(pdata, MMC_RXOVERSIZE_G);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX64OCTETS_GB_POS,
				MMC_RISR_RX64OCTETS_GB_LEN))
		stats->rx64octets_gb +=
			xlgmac_mmc_read(pdata, MMC_RX64OCTETS_GB_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX65TO127OCTETS_GB_POS,
				MMC_RISR_RX65TO127OCTETS_GB_LEN))
		stats->rx65to127octets_gb +=
			xlgmac_mmc_read(pdata, MMC_RX65TO127OCTETS_GB_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX128TO255OCTETS_GB_POS,
				MMC_RISR_RX128TO255OCTETS_GB_LEN))
		stats->rx128to255octets_gb +=
			xlgmac_mmc_read(pdata, MMC_RX128TO255OCTETS_GB_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX256TO511OCTETS_GB_POS,
				MMC_RISR_RX256TO511OCTETS_GB_LEN))
		stats->rx256to511octets_gb +=
			xlgmac_mmc_read(pdata, MMC_RX256TO511OCTETS_GB_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX512TO1023OCTETS_GB_POS,
				MMC_RISR_RX512TO1023OCTETS_GB_LEN))
		stats->rx512to1023octets_gb +=
			xlgmac_mmc_read(pdata, MMC_RX512TO1023OCTETS_GB_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX1024TOMAXOCTETS_GB_POS,
				MMC_RISR_RX1024TOMAXOCTETS_GB_LEN))
		stats->rx1024tomaxoctets_gb +=
			xlgmac_mmc_read(pdata, MMC_RX1024TOMAXOCTETS_GB_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXUNICASTFRAMES_G_POS,
				MMC_RISR_RXUNICASTFRAMES_G_LEN))
		stats->rxunicastframes_g +=
			xlgmac_mmc_read(pdata, MMC_RXUNICASTFRAMES_G_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXLENGTHERROR_POS,
				MMC_RISR_RXLENGTHERROR_LEN))
		stats->rxlengtherror +=
			xlgmac_mmc_read(pdata, MMC_RXLENGTHERROR_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXOUTOFRANGETYPE_POS,
				MMC_RISR_RXOUTOFRANGETYPE_LEN))
		stats->rxoutofrangetype +=
			xlgmac_mmc_read(pdata, MMC_RXOUTOFRANGETYPE_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXPAUSEFRAMES_POS,
				MMC_RISR_RXPAUSEFRAMES_LEN))
		stats->rxpauseframes +=
			xlgmac_mmc_read(pdata, MMC_RXPAUSEFRAMES_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXFIFOOVERFLOW_POS,
				MMC_RISR_RXFIFOOVERFLOW_LEN))
		stats->rxfifooverflow +=
			xlgmac_mmc_read(pdata, MMC_RXFIFOOVERFLOW_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXVLANFRAMES_GB_POS,
				MMC_RISR_RXVLANFRAMES_GB_LEN))
		stats->rxvlanframes_gb +=
			xlgmac_mmc_read(pdata, MMC_RXVLANFRAMES_GB_LO);

	if (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXWATCHDOGERROR_POS,
				MMC_RISR_RXWATCHDOGERROR_LEN))
		stats->rxwatchdogerror +=
			xlgmac_mmc_read(pdata, MMC_RXWATCHDOGERROR);
}