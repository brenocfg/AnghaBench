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
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int dummy; } ;
struct sdhci_esdhc {scalar_t__ vendor_ver; int quirk_ignore_data_inhibit; } ;

/* Variables and functions */
 int SDHCI_CAN_DO_ADMA1 ; 
 int SDHCI_CAN_DO_ADMA2 ; 
 int SDHCI_CAPABILITIES ; 
 int SDHCI_CAPABILITIES_1 ; 
 int SDHCI_CMD_LVL ; 
 int SDHCI_DATA_INHIBIT ; 
 int SDHCI_DATA_LVL_MASK ; 
 int SDHCI_PRESENT_STATE ; 
 int SDHCI_SUPPORT_DDR50 ; 
 int SDHCI_SUPPORT_SDR104 ; 
 int SDHCI_SUPPORT_SDR50 ; 
 scalar_t__ VENDOR_V_22 ; 
 struct sdhci_esdhc* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static u32 esdhc_readl_fixup(struct sdhci_host *host,
				     int spec_reg, u32 value)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	u32 ret;

	/*
	 * The bit of ADMA flag in eSDHC is not compatible with standard
	 * SDHC register, so set fake flag SDHCI_CAN_DO_ADMA2 when ADMA is
	 * supported by eSDHC.
	 * And for many FSL eSDHC controller, the reset value of field
	 * SDHCI_CAN_DO_ADMA1 is 1, but some of them can't support ADMA,
	 * only these vendor version is greater than 2.2/0x12 support ADMA.
	 */
	if ((spec_reg == SDHCI_CAPABILITIES) && (value & SDHCI_CAN_DO_ADMA1)) {
		if (esdhc->vendor_ver > VENDOR_V_22) {
			ret = value | SDHCI_CAN_DO_ADMA2;
			return ret;
		}
	}
	/*
	 * The DAT[3:0] line signal levels and the CMD line signal level are
	 * not compatible with standard SDHC register. The line signal levels
	 * DAT[7:0] are at bits 31:24 and the command line signal level is at
	 * bit 23. All other bits are the same as in the standard SDHC
	 * register.
	 */
	if (spec_reg == SDHCI_PRESENT_STATE) {
		ret = value & 0x000fffff;
		ret |= (value >> 4) & SDHCI_DATA_LVL_MASK;
		ret |= (value << 1) & SDHCI_CMD_LVL;
		return ret;
	}

	/*
	 * DTS properties of mmc host are used to enable each speed mode
	 * according to soc and board capability. So clean up
	 * SDR50/SDR104/DDR50 support bits here.
	 */
	if (spec_reg == SDHCI_CAPABILITIES_1) {
		ret = value & ~(SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_SDR104 |
				SDHCI_SUPPORT_DDR50);
		return ret;
	}

	/*
	 * Some controllers have unreliable Data Line Active
	 * bit for commands with busy signal. This affects
	 * Command Inhibit (data) bit. Just ignore it since
	 * MMC core driver has already polled card status
	 * with CMD13 after any command with busy siganl.
	 */
	if ((spec_reg == SDHCI_PRESENT_STATE) &&
	(esdhc->quirk_ignore_data_inhibit == true)) {
		ret = value & ~SDHCI_DATA_INHIBIT;
		return ret;
	}

	ret = value;
	return ret;
}