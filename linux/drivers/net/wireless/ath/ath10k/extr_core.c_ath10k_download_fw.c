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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {scalar_t__ fw_diag_ce_download; int /*<<< orphan*/  patch_load_addr; } ;
struct ath10k {TYPE_2__ hw_params; TYPE_1__* running_fw; } ;
struct TYPE_6__ {void* firmware_data; int /*<<< orphan*/  firmware_len; } ;
struct TYPE_4__ {TYPE_3__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int ath10k_bmi_fast_download (struct ath10k*,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int ath10k_hw_diag_fast_download (struct ath10k*,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int ath10k_swap_code_seg_configure (struct ath10k*,TYPE_3__*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 

__attribute__((used)) static int ath10k_download_fw(struct ath10k *ar)
{
	u32 address, data_len;
	const void *data;
	int ret;

	address = ar->hw_params.patch_load_addr;

	data = ar->running_fw->fw_file.firmware_data;
	data_len = ar->running_fw->fw_file.firmware_len;

	ret = ath10k_swap_code_seg_configure(ar, &ar->running_fw->fw_file);
	if (ret) {
		ath10k_err(ar, "failed to configure fw code swap: %d\n",
			   ret);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot uploading firmware image %pK len %d\n",
		   data, data_len);

	/* Check if device supports to download firmware via
	 * diag copy engine. Downloading firmware via diag CE
	 * greatly reduces the time to download firmware.
	 */
	if (ar->hw_params.fw_diag_ce_download) {
		ret = ath10k_hw_diag_fast_download(ar, address,
						   data, data_len);
		if (ret == 0)
			/* firmware upload via diag ce was successful */
			return 0;

		ath10k_warn(ar,
			    "failed to upload firmware via diag ce, trying BMI: %d",
			    ret);
	}

	return ath10k_bmi_fast_download(ar, address,
					data, data_len);
}