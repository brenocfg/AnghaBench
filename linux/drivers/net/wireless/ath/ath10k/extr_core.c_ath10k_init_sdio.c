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
struct ath10k {int dummy; } ;
typedef  enum ath10k_firmware_mode { ____Placeholder_ath10k_firmware_mode } ath10k_firmware_mode ;

/* Variables and functions */
 int ATH10K_FIRMWARE_MODE_UTF ; 
 int HI_ACS_FLAGS_ALT_DATA_CREDIT_SIZE ; 
 int HI_ACS_FLAGS_SDIO_REDUCE_TX_COMPL_SET ; 
 int HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_SET ; 
 int HI_OPTION_DISABLE_DBGLOG ; 
 int /*<<< orphan*/  ath10k_bmi_read32 (struct ath10k*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ath10k_bmi_write32 (struct ath10k*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hi_acs_flags ; 
 int /*<<< orphan*/  hi_mbox_io_block_sz ; 
 int /*<<< orphan*/  hi_mbox_isr_yield_limit ; 
 int /*<<< orphan*/  hi_option_flag ; 

__attribute__((used)) static void ath10k_init_sdio(struct ath10k *ar, enum ath10k_firmware_mode mode)
{
	u32 param = 0;

	ath10k_bmi_write32(ar, hi_mbox_io_block_sz, 256);
	ath10k_bmi_write32(ar, hi_mbox_isr_yield_limit, 99);
	ath10k_bmi_read32(ar, hi_acs_flags, &param);

	/* Data transfer is not initiated, when reduced Tx completion
	 * is used for SDIO. disable it until fixed
	 */
	param &= ~HI_ACS_FLAGS_SDIO_REDUCE_TX_COMPL_SET;

	/* Alternate credit size of 1544 as used by SDIO firmware is
	 * not big enough for mac80211 / native wifi frames. disable it
	 */
	param &= ~HI_ACS_FLAGS_ALT_DATA_CREDIT_SIZE;

	if (mode == ATH10K_FIRMWARE_MODE_UTF)
		param &= ~HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_SET;
	else
		param |= HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_SET;

	ath10k_bmi_write32(ar, hi_acs_flags, param);

	/* Explicitly set fwlog prints to zero as target may turn it on
	 * based on scratch registers.
	 */
	ath10k_bmi_read32(ar, hi_option_flag, &param);
	param |= HI_OPTION_DISABLE_DBGLOG;
	ath10k_bmi_write32(ar, hi_option_flag, param);
}