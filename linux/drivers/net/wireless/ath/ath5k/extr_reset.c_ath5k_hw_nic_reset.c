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
typedef  unsigned int u32 ;
struct ath5k_hw {scalar_t__ ah_version; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_CFG ; 
 unsigned int AR5K_INIT_CFG ; 
 int /*<<< orphan*/  AR5K_RESET_CTL ; 
 unsigned int AR5K_RESET_CTL_BASEBAND ; 
 unsigned int AR5K_RESET_CTL_DMA ; 
 unsigned int AR5K_RESET_CTL_MAC ; 
 unsigned int AR5K_RESET_CTL_PCU ; 
 unsigned int AR5K_RESET_CTL_PHY ; 
 int /*<<< orphan*/  AR5K_RXDP ; 
 int /*<<< orphan*/  ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int ath5k_hw_register_timeout (struct ath5k_hw*,int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
ath5k_hw_nic_reset(struct ath5k_hw *ah, u32 val)
{
	int ret;
	u32 mask = val ? val : ~0U;

	/* Read-and-clear RX Descriptor Pointer*/
	ath5k_hw_reg_read(ah, AR5K_RXDP);

	/*
	 * Reset the device and wait until success
	 */
	ath5k_hw_reg_write(ah, val, AR5K_RESET_CTL);

	/* Wait at least 128 PCI clocks */
	usleep_range(15, 20);

	if (ah->ah_version == AR5K_AR5210) {
		val &= AR5K_RESET_CTL_PCU | AR5K_RESET_CTL_DMA
			| AR5K_RESET_CTL_MAC | AR5K_RESET_CTL_PHY;
		mask &= AR5K_RESET_CTL_PCU | AR5K_RESET_CTL_DMA
			| AR5K_RESET_CTL_MAC | AR5K_RESET_CTL_PHY;
	} else {
		val &= AR5K_RESET_CTL_PCU | AR5K_RESET_CTL_BASEBAND;
		mask &= AR5K_RESET_CTL_PCU | AR5K_RESET_CTL_BASEBAND;
	}

	ret = ath5k_hw_register_timeout(ah, AR5K_RESET_CTL, mask, val, false);

	/*
	 * Reset configuration register (for hw byte-swap). Note that this
	 * is only set for big endian. We do the necessary magic in
	 * AR5K_INIT_CFG.
	 */
	if ((val & AR5K_RESET_CTL_PCU) == 0)
		ath5k_hw_reg_write(ah, AR5K_INIT_CFG, AR5K_CFG);

	return ret;
}