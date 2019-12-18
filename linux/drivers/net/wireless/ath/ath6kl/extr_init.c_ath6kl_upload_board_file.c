#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ target_ver; } ;
struct TYPE_3__ {scalar_t__ board_addr; } ;
struct ath6kl {int target_type; scalar_t__ fw_board_len; TYPE_2__ version; int /*<<< orphan*/ * fw_board; TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ AR6003_BOARD_DATA_SZ ; 
 scalar_t__ AR6003_BOARD_EXT_DATA_SZ ; 
 scalar_t__ AR6003_BOARD_EXT_DATA_SZ_V2 ; 
 scalar_t__ AR6004_BOARD_DATA_SZ ; 
 scalar_t__ AR6004_BOARD_EXT_DATA_SZ ; 
 scalar_t__ AR6004_HW_1_3_VERSION ; 
 scalar_t__ AR6004_HW_3_0_VERSION ; 
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int EINVAL ; 
 int ENOENT ; 
#define  TARGET_TYPE_AR6003 129 
#define  TARGET_TYPE_AR6004 128 
 scalar_t__ WARN_ON (int) ; 
 int ath6kl_bmi_read_hi32 (struct ath6kl*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ath6kl_bmi_write (struct ath6kl*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ath6kl_bmi_write_hi32 (struct ath6kl*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ath6kl_err (char*,...) ; 
 int /*<<< orphan*/  hi_board_data ; 
 int /*<<< orphan*/  hi_board_data_initialized ; 
 int /*<<< orphan*/  hi_board_ext_data ; 
 int /*<<< orphan*/  hi_board_ext_data_config ; 

__attribute__((used)) static int ath6kl_upload_board_file(struct ath6kl *ar)
{
	u32 board_address, board_ext_address, param;
	u32 board_data_size, board_ext_data_size;
	int ret;

	if (WARN_ON(ar->fw_board == NULL))
		return -ENOENT;

	/*
	 * Determine where in Target RAM to write Board Data.
	 * For AR6004, host determine Target RAM address for
	 * writing board data.
	 */
	if (ar->hw.board_addr != 0) {
		board_address = ar->hw.board_addr;
		ath6kl_bmi_write_hi32(ar, hi_board_data,
				      board_address);
	} else {
		ret = ath6kl_bmi_read_hi32(ar, hi_board_data, &board_address);
		if (ret) {
			ath6kl_err("Failed to get board file target address.\n");
			return ret;
		}
	}

	/* determine where in target ram to write extended board data */
	ret = ath6kl_bmi_read_hi32(ar, hi_board_ext_data, &board_ext_address);
	if (ret) {
		ath6kl_err("Failed to get extended board file target address.\n");
		return ret;
	}

	if (ar->target_type == TARGET_TYPE_AR6003 &&
	    board_ext_address == 0) {
		ath6kl_err("Failed to get board file target address.\n");
		return -EINVAL;
	}

	switch (ar->target_type) {
	case TARGET_TYPE_AR6003:
		board_data_size = AR6003_BOARD_DATA_SZ;
		board_ext_data_size = AR6003_BOARD_EXT_DATA_SZ;
		if (ar->fw_board_len > (board_data_size + board_ext_data_size))
			board_ext_data_size = AR6003_BOARD_EXT_DATA_SZ_V2;
		break;
	case TARGET_TYPE_AR6004:
		board_data_size = AR6004_BOARD_DATA_SZ;
		board_ext_data_size = AR6004_BOARD_EXT_DATA_SZ;
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	if (board_ext_address &&
	    ar->fw_board_len == (board_data_size + board_ext_data_size)) {
		/* write extended board data */
		ath6kl_dbg(ATH6KL_DBG_BOOT,
			   "writing extended board data to 0x%x (%d B)\n",
			   board_ext_address, board_ext_data_size);

		ret = ath6kl_bmi_write(ar, board_ext_address,
				       ar->fw_board + board_data_size,
				       board_ext_data_size);
		if (ret) {
			ath6kl_err("Failed to write extended board data: %d\n",
				   ret);
			return ret;
		}

		/* record that extended board data is initialized */
		param = (board_ext_data_size << 16) | 1;

		ath6kl_bmi_write_hi32(ar, hi_board_ext_data_config, param);
	}

	if (ar->fw_board_len < board_data_size) {
		ath6kl_err("Too small board file: %zu\n", ar->fw_board_len);
		ret = -EINVAL;
		return ret;
	}

	ath6kl_dbg(ATH6KL_DBG_BOOT, "writing board file to 0x%x (%d B)\n",
		   board_address, board_data_size);

	ret = ath6kl_bmi_write(ar, board_address, ar->fw_board,
			       board_data_size);

	if (ret) {
		ath6kl_err("Board file bmi write failed: %d\n", ret);
		return ret;
	}

	/* record the fact that Board Data IS initialized */
	if ((ar->version.target_ver == AR6004_HW_1_3_VERSION) ||
	    (ar->version.target_ver == AR6004_HW_3_0_VERSION))
		param = board_data_size;
	else
		param = 1;

	ath6kl_bmi_write_hi32(ar, hi_board_data_initialized, param);

	return ret;
}