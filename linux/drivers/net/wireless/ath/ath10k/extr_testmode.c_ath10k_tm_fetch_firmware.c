#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  otp_len; scalar_t__ otp_data; } ;
struct ath10k_fw_components {TYPE_5__ fw_file; int /*<<< orphan*/  board_len; int /*<<< orphan*/  board_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  otp_len; scalar_t__ otp_data; } ;
struct TYPE_10__ {TYPE_3__ fw_file; int /*<<< orphan*/  board_len; int /*<<< orphan*/  board_data; } ;
struct TYPE_8__ {struct ath10k_fw_components utf_mode_fw; } ;
struct TYPE_7__ {int bus; } ;
struct ath10k {TYPE_4__ normal_mode_fw; TYPE_2__ testmode; TYPE_1__ hif; } ;
typedef  int /*<<< orphan*/  fw_name ;

/* Variables and functions */
#define  ATH10K_BUS_SDIO 129 
#define  ATH10K_BUS_USB 128 
 int /*<<< orphan*/  ATH10K_DBG_TESTMODE ; 
 int /*<<< orphan*/  ATH10K_FW_UTF_FILE_BASE ; 
 int /*<<< orphan*/  ath10k_bus_str (int) ; 
 int ath10k_core_fetch_firmware_api_n (struct ath10k*,char*,TYPE_5__*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ath10k_info (struct ath10k*,char*) ; 
 int ath10k_tm_fetch_utf_firmware_api_1 (struct ath10k*,TYPE_5__*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static int ath10k_tm_fetch_firmware(struct ath10k *ar)
{
	struct ath10k_fw_components *utf_mode_fw;
	int ret;
	char fw_name[100];
	int fw_api2 = 2;

	switch (ar->hif.bus) {
	case ATH10K_BUS_SDIO:
	case ATH10K_BUS_USB:
		scnprintf(fw_name, sizeof(fw_name), "%s-%s-%d.bin",
			  ATH10K_FW_UTF_FILE_BASE, ath10k_bus_str(ar->hif.bus),
			  fw_api2);
		break;
	default:
		scnprintf(fw_name, sizeof(fw_name), "%s-%d.bin",
			  ATH10K_FW_UTF_FILE_BASE, fw_api2);
		break;
	}

	ret = ath10k_core_fetch_firmware_api_n(ar, fw_name,
					       &ar->testmode.utf_mode_fw.fw_file);
	if (ret == 0) {
		ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode using fw utf api 2");
		goto out;
	}

	ret = ath10k_tm_fetch_utf_firmware_api_1(ar, &ar->testmode.utf_mode_fw.fw_file);
	if (ret) {
		ath10k_err(ar, "failed to fetch utf firmware binary: %d", ret);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode using utf api 1");

out:
	utf_mode_fw = &ar->testmode.utf_mode_fw;

	/* Use the same board data file as the normal firmware uses (but
	 * it's still "owned" by normal_mode_fw so we shouldn't free it.
	 */
	utf_mode_fw->board_data = ar->normal_mode_fw.board_data;
	utf_mode_fw->board_len = ar->normal_mode_fw.board_len;

	if (!utf_mode_fw->fw_file.otp_data) {
		ath10k_info(ar, "utf.bin didn't contain otp binary, taking it from the normal mode firmware");
		utf_mode_fw->fw_file.otp_data = ar->normal_mode_fw.fw_file.otp_data;
		utf_mode_fw->fw_file.otp_len = ar->normal_mode_fw.fw_file.otp_len;
	}

	return 0;
}