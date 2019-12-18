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
struct ath10k_fw_file {TYPE_3__* firmware; int /*<<< orphan*/  firmware_len; int /*<<< orphan*/  firmware_data; int /*<<< orphan*/  htt_op_version; int /*<<< orphan*/  wmi_op_version; } ;
struct TYPE_4__ {char* dir; } ;
struct TYPE_5__ {TYPE_1__ fw; } ;
struct ath10k {int /*<<< orphan*/  dev; TYPE_2__ hw_params; } ;
typedef  int /*<<< orphan*/  filename ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_TESTMODE ; 
 int /*<<< orphan*/  ATH10K_FW_HTT_OP_VERSION_10_1 ; 
 char* ATH10K_FW_UTF_FILE ; 
 int /*<<< orphan*/  ATH10K_FW_WMI_OP_VERSION_10_1 ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,char*,int) ; 
 int firmware_request_nowarn (TYPE_3__**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int ath10k_tm_fetch_utf_firmware_api_1(struct ath10k *ar,
					      struct ath10k_fw_file *fw_file)
{
	char filename[100];
	int ret;

	snprintf(filename, sizeof(filename), "%s/%s",
		 ar->hw_params.fw.dir, ATH10K_FW_UTF_FILE);

	/* load utf firmware image */
	ret = firmware_request_nowarn(&fw_file->firmware, filename, ar->dev);
	ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode fw request '%s': %d\n",
		   filename, ret);

	if (ret) {
		ath10k_warn(ar, "failed to retrieve utf firmware '%s': %d\n",
			    filename, ret);
		return ret;
	}

	/* We didn't find FW UTF API 1 ("utf.bin") does not advertise
	 * firmware features. Do an ugly hack where we force the firmware
	 * features to match with 10.1 branch so that wmi.c will use the
	 * correct WMI interface.
	 */

	fw_file->wmi_op_version = ATH10K_FW_WMI_OP_VERSION_10_1;
	fw_file->htt_op_version = ATH10K_FW_HTT_OP_VERSION_10_1;
	fw_file->firmware_data = fw_file->firmware->data;
	fw_file->firmware_len = fw_file->firmware->size;

	return 0;
}