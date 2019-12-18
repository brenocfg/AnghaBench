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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int ath10k_core_get_board_id_from_otp (struct ath10k*) ; 
 int ath10k_core_pre_cal_download (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,...) ; 
 int ath10k_download_and_run_otp (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 

__attribute__((used)) static int ath10k_core_pre_cal_config(struct ath10k *ar)
{
	int ret;

	ret = ath10k_core_pre_cal_download(ar);
	if (ret) {
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "failed to load pre cal data: %d\n", ret);
		return ret;
	}

	ret = ath10k_core_get_board_id_from_otp(ar);
	if (ret) {
		ath10k_err(ar, "failed to get board id: %d\n", ret);
		return ret;
	}

	ret = ath10k_download_and_run_otp(ar);
	if (ret) {
		ath10k_err(ar, "failed to run otp: %d\n", ret);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "pre cal configuration done successfully\n");

	return 0;
}