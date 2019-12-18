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
struct sdio_func {int dummy; } ;
struct ath10k_sdio {int is_disabled; struct sdio_func* func; } ;
struct ath10k {int dummy; } ;
typedef  enum ath10k_firmware_mode { ____Placeholder_ath10k_firmware_mode } ath10k_firmware_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int ath10k_sdio_config (struct ath10k*) ; 
 int ath10k_sdio_hif_disable_intrs (struct ath10k*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int sdio_enable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 

__attribute__((used)) static int ath10k_sdio_hif_power_up(struct ath10k *ar,
				    enum ath10k_firmware_mode fw_mode)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct sdio_func *func = ar_sdio->func;
	int ret;

	if (!ar_sdio->is_disabled)
		return 0;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "sdio power on\n");

	ret = ath10k_sdio_config(ar);
	if (ret) {
		ath10k_err(ar, "failed to config sdio: %d\n", ret);
		return ret;
	}

	sdio_claim_host(func);

	ret = sdio_enable_func(func);
	if (ret) {
		ath10k_warn(ar, "unable to enable sdio function: %d)\n", ret);
		sdio_release_host(func);
		return ret;
	}

	sdio_release_host(func);

	/* Wait for hardware to initialise. It should take a lot less than
	 * 20 ms but let's be conservative here.
	 */
	msleep(20);

	ar_sdio->is_disabled = false;

	ret = ath10k_sdio_hif_disable_intrs(ar);
	if (ret)
		return ret;

	return 0;
}