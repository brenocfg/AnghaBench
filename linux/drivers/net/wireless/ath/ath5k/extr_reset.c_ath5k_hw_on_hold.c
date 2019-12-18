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
struct pci_dev {int dummy; } ;
struct ath5k_hw {scalar_t__ ah_version; struct pci_dev* pdev; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_PM_AWAKE ; 
 int AR5K_RESET_CTL_BASEBAND ; 
 int AR5K_RESET_CTL_DMA ; 
 int AR5K_RESET_CTL_MAC ; 
 int AR5K_RESET_CTL_PCI ; 
 int AR5K_RESET_CTL_PCU ; 
 int AR5K_RESET_CTL_PHY ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*) ; 
 scalar_t__ ATH_AHB ; 
 int EIO ; 
 scalar_t__ ath5k_get_bus_type (struct ath5k_hw*) ; 
 int ath5k_hw_nic_reset (struct ath5k_hw*,int) ; 
 int ath5k_hw_set_power_mode (struct ath5k_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int
ath5k_hw_on_hold(struct ath5k_hw *ah)
{
	struct pci_dev *pdev = ah->pdev;
	u32 bus_flags;
	int ret;

	if (ath5k_get_bus_type(ah) == ATH_AHB)
		return 0;

	/* Make sure device is awake */
	ret = ath5k_hw_set_power_mode(ah, AR5K_PM_AWAKE, true, 0);
	if (ret) {
		ATH5K_ERR(ah, "failed to wakeup the MAC Chip\n");
		return ret;
	}

	/*
	 * Put chipset on warm reset...
	 *
	 * Note: putting PCI core on warm reset on PCI-E cards
	 * results card to hang and always return 0xffff... so
	 * we ignore that flag for PCI-E cards. On PCI cards
	 * this flag gets cleared after 64 PCI clocks.
	 */
	bus_flags = (pdev && pci_is_pcie(pdev)) ? 0 : AR5K_RESET_CTL_PCI;

	if (ah->ah_version == AR5K_AR5210) {
		ret = ath5k_hw_nic_reset(ah, AR5K_RESET_CTL_PCU |
			AR5K_RESET_CTL_MAC | AR5K_RESET_CTL_DMA |
			AR5K_RESET_CTL_PHY | AR5K_RESET_CTL_PCI);
		usleep_range(2000, 2500);
	} else {
		ret = ath5k_hw_nic_reset(ah, AR5K_RESET_CTL_PCU |
			AR5K_RESET_CTL_BASEBAND | bus_flags);
	}

	if (ret) {
		ATH5K_ERR(ah, "failed to put device on warm reset\n");
		return -EIO;
	}

	/* ...wakeup again!*/
	ret = ath5k_hw_set_power_mode(ah, AR5K_PM_AWAKE, true, 0);
	if (ret) {
		ATH5K_ERR(ah, "failed to put device on hold\n");
		return ret;
	}

	return ret;
}