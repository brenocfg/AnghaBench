#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ath10k_sdio {int is_disabled; TYPE_2__* func; } ;
struct ath10k {int dummy; } ;
struct TYPE_6__ {TYPE_1__* card; } ;
struct TYPE_5__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int mmc_hw_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (TYPE_2__*) ; 
 int sdio_disable_func (TYPE_2__*) ; 
 int /*<<< orphan*/  sdio_release_host (TYPE_2__*) ; 

__attribute__((used)) static void ath10k_sdio_hif_power_down(struct ath10k *ar)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	int ret;

	if (ar_sdio->is_disabled)
		return;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "sdio power off\n");

	/* Disable the card */
	sdio_claim_host(ar_sdio->func);

	ret = sdio_disable_func(ar_sdio->func);
	if (ret) {
		ath10k_warn(ar, "unable to disable sdio function: %d\n", ret);
		sdio_release_host(ar_sdio->func);
		return;
	}

	ret = mmc_hw_reset(ar_sdio->func->card->host);
	if (ret)
		ath10k_warn(ar, "unable to reset sdio: %d\n", ret);

	sdio_release_host(ar_sdio->func);

	ar_sdio->is_disabled = true;
}