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
struct TYPE_3__ {int dir; } ;
struct TYPE_4__ {TYPE_1__ fw; } ;
struct ath10k {int bd_api; TYPE_2__ hw_params; } ;
typedef  int /*<<< orphan*/  boardname ;

/* Variables and functions */
 int ATH10K_BD_IE_BOARD ; 
 int ATH10K_BD_IE_BOARD_EXT ; 
 int /*<<< orphan*/  ATH10K_BOARD_API2_FILE ; 
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int ath10k_core_create_board_name (struct ath10k*,char*,int,int) ; 
 int ath10k_core_create_eboard_name (struct ath10k*,char*,int) ; 
 int ath10k_core_fetch_board_data_api_1 (struct ath10k*,int) ; 
 int ath10k_core_fetch_board_data_api_n (struct ath10k*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,...) ; 

int ath10k_core_fetch_board_file(struct ath10k *ar, int bd_ie_type)
{
	char boardname[100], fallback_boardname[100];
	int ret;

	if (bd_ie_type == ATH10K_BD_IE_BOARD) {
		ret = ath10k_core_create_board_name(ar, boardname,
						    sizeof(boardname), true);
		if (ret) {
			ath10k_err(ar, "failed to create board name: %d", ret);
			return ret;
		}

		ret = ath10k_core_create_board_name(ar, fallback_boardname,
						    sizeof(boardname), false);
		if (ret) {
			ath10k_err(ar, "failed to create fallback board name: %d", ret);
			return ret;
		}
	} else if (bd_ie_type == ATH10K_BD_IE_BOARD_EXT) {
		ret = ath10k_core_create_eboard_name(ar, boardname,
						     sizeof(boardname));
		if (ret) {
			ath10k_err(ar, "fallback to eboard.bin since board id 0");
			goto fallback;
		}
	}

	ar->bd_api = 2;
	ret = ath10k_core_fetch_board_data_api_n(ar, boardname,
						 fallback_boardname,
						 ATH10K_BOARD_API2_FILE);
	if (!ret)
		goto success;

fallback:
	ar->bd_api = 1;
	ret = ath10k_core_fetch_board_data_api_1(ar, bd_ie_type);
	if (ret) {
		ath10k_err(ar, "failed to fetch board-2.bin or board.bin from %s\n",
			   ar->hw_params.fw.dir);
		return ret;
	}

success:
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "using board api %d\n", ar->bd_api);
	return 0;
}