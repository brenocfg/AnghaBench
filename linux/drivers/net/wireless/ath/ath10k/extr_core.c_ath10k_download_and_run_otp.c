#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int patch_load_addr; int otp_exe_param; } ;
struct ath10k {scalar_t__ cal_mode; TYPE_3__* running_fw; TYPE_1__ hw_params; } ;
struct TYPE_5__ {int /*<<< orphan*/  fw_features; int /*<<< orphan*/  otp_len; int /*<<< orphan*/  otp_data; } ;
struct TYPE_6__ {TYPE_2__ fw_file; int /*<<< orphan*/  board_len; int /*<<< orphan*/  board_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ATH10K_FW_FEATURE_IGNORE_OTP_RESULT ; 
 scalar_t__ ATH10K_PRE_CAL_MODE_DT ; 
 scalar_t__ ATH10K_PRE_CAL_MODE_FILE ; 
 int BMI_PARAM_FLASH_SECTION_ALL ; 
 int EINVAL ; 
 int ath10k_bmi_execute (struct ath10k*,int,int,int*) ; 
 int ath10k_bmi_fast_download (struct ath10k*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,...) ; 
 int ath10k_download_board_data (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_otp ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_download_and_run_otp(struct ath10k *ar)
{
	u32 result, address = ar->hw_params.patch_load_addr;
	u32 bmi_otp_exe_param = ar->hw_params.otp_exe_param;
	int ret;

	ret = ath10k_download_board_data(ar,
					 ar->running_fw->board_data,
					 ar->running_fw->board_len);
	if (ret) {
		ath10k_err(ar, "failed to download board data: %d\n", ret);
		return ret;
	}

	/* OTP is optional */

	if (!ar->running_fw->fw_file.otp_data ||
	    !ar->running_fw->fw_file.otp_len) {
		ath10k_warn(ar, "Not running otp, calibration will be incorrect (otp-data %pK otp_len %zd)!\n",
			    ar->running_fw->fw_file.otp_data,
			    ar->running_fw->fw_file.otp_len);
		return 0;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot upload otp to 0x%x len %zd\n",
		   address, ar->running_fw->fw_file.otp_len);

	ret = ath10k_bmi_fast_download(ar, address,
				       ar->running_fw->fw_file.otp_data,
				       ar->running_fw->fw_file.otp_len);
	if (ret) {
		ath10k_err(ar, "could not write otp (%d)\n", ret);
		return ret;
	}

	/* As of now pre-cal is valid for 10_4 variants */
	if (ar->cal_mode == ATH10K_PRE_CAL_MODE_DT ||
	    ar->cal_mode == ATH10K_PRE_CAL_MODE_FILE)
		bmi_otp_exe_param = BMI_PARAM_FLASH_SECTION_ALL;

	ret = ath10k_bmi_execute(ar, address, bmi_otp_exe_param, &result);
	if (ret) {
		ath10k_err(ar, "could not execute otp (%d)\n", ret);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot otp execute result %d\n", result);

	if (!(skip_otp || test_bit(ATH10K_FW_FEATURE_IGNORE_OTP_RESULT,
				   ar->running_fw->fw_file.fw_features)) &&
	    result != 0) {
		ath10k_err(ar, "otp calibration failed: %d", result);
		return -EINVAL;
	}

	return 0;
}