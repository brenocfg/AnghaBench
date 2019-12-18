#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int /*<<< orphan*/  dir; } ;
struct TYPE_9__ {TYPE_2__ fw; } ;
struct TYPE_7__ {TYPE_4__* board; } ;
struct ath10k {TYPE_3__ hw_params; TYPE_1__ normal_mode_fw; } ;
struct TYPE_10__ {size_t size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int /*<<< orphan*/  ATH10K_BOARD_MAGIC ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (TYPE_4__*) ; 
 int PTR_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  ath10k_core_free_board_files (struct ath10k*) ; 
 int ath10k_core_search_bd (struct ath10k*,char const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,...) ; 
 TYPE_4__* ath10k_fetch_fw_file (struct ath10k*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_core_fetch_board_data_api_n(struct ath10k *ar,
					      const char *boardname,
					      const char *fallback_boardname,
					      const char *filename)
{
	size_t len, magic_len;
	const u8 *data;
	int ret;

	/* Skip if already fetched during board data download */
	if (!ar->normal_mode_fw.board)
		ar->normal_mode_fw.board = ath10k_fetch_fw_file(ar,
								ar->hw_params.fw.dir,
								filename);
	if (IS_ERR(ar->normal_mode_fw.board))
		return PTR_ERR(ar->normal_mode_fw.board);

	data = ar->normal_mode_fw.board->data;
	len = ar->normal_mode_fw.board->size;

	/* magic has extra null byte padded */
	magic_len = strlen(ATH10K_BOARD_MAGIC) + 1;
	if (len < magic_len) {
		ath10k_err(ar, "failed to find magic value in %s/%s, file too short: %zu\n",
			   ar->hw_params.fw.dir, filename, len);
		ret = -EINVAL;
		goto err;
	}

	if (memcmp(data, ATH10K_BOARD_MAGIC, magic_len)) {
		ath10k_err(ar, "found invalid board magic\n");
		ret = -EINVAL;
		goto err;
	}

	/* magic is padded to 4 bytes */
	magic_len = ALIGN(magic_len, 4);
	if (len < magic_len) {
		ath10k_err(ar, "failed: %s/%s too small to contain board data, len: %zu\n",
			   ar->hw_params.fw.dir, filename, len);
		ret = -EINVAL;
		goto err;
	}

	data += magic_len;
	len -= magic_len;

	/* attempt to find boardname in the IE list */
	ret = ath10k_core_search_bd(ar, boardname, data, len);

	/* if we didn't find it and have a fallback name, try that */
	if (ret == -ENOENT && fallback_boardname)
		ret = ath10k_core_search_bd(ar, fallback_boardname, data, len);

	if (ret == -ENOENT) {
		ath10k_err(ar,
			   "failed to fetch board data for %s from %s/%s\n",
			   boardname, ar->hw_params.fw.dir, filename);
		ret = -ENODATA;
	}

	if (ret)
		goto err;

	return 0;

err:
	ath10k_core_free_board_files(ar);
	return ret;
}