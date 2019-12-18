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
struct ath10k_sdio {int swap_mbox; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SDIO ; 
 int HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_FW_ACK ; 
 int /*<<< orphan*/  HI_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int ath10k_sdio_hif_diag_read32 (struct ath10k*,int,int*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  hi_acs_flags ; 
 int host_interest_item_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_sdio_hif_swap_mailbox(struct ath10k *ar)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	u32 addr, val;
	int ret = 0;

	addr = host_interest_item_address(HI_ITEM(hi_acs_flags));

	ret = ath10k_sdio_hif_diag_read32(ar, addr, &val);
	if (ret) {
		ath10k_warn(ar, "unable to read hi_acs_flags : %d\n", ret);
		return ret;
	}

	if (val & HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_FW_ACK) {
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio mailbox swap service enabled\n");
		ar_sdio->swap_mbox = true;
	} else {
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio mailbox swap service disabled\n");
		ar_sdio->swap_mbox = false;
	}

	return 0;
}