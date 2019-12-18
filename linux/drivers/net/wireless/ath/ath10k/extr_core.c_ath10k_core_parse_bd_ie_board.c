#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath10k_fw_ie {void* data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {size_t board_len; size_t ext_board_len; void const* ext_board_data; void const* board_data; } ;
struct ath10k {TYPE_1__ normal_mode_fw; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int ATH10K_BD_IE_BOARD ; 
#define  ATH10K_BD_IE_BOARD_DATA 129 
 int ATH10K_BD_IE_BOARD_EXT ; 
#define  ATH10K_BD_IE_BOARD_NAME 128 
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ath10k_dbg_dump (struct ath10k*,int /*<<< orphan*/ ,char*,char*,void const*,size_t) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int memcmp (void const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int ath10k_core_parse_bd_ie_board(struct ath10k *ar,
					 const void *buf, size_t buf_len,
					 const char *boardname,
					 int bd_ie_type)
{
	const struct ath10k_fw_ie *hdr;
	bool name_match_found;
	int ret, board_ie_id;
	size_t board_ie_len;
	const void *board_ie_data;

	name_match_found = false;

	/* go through ATH10K_BD_IE_BOARD_ elements */
	while (buf_len > sizeof(struct ath10k_fw_ie)) {
		hdr = buf;
		board_ie_id = le32_to_cpu(hdr->id);
		board_ie_len = le32_to_cpu(hdr->len);
		board_ie_data = hdr->data;

		buf_len -= sizeof(*hdr);
		buf += sizeof(*hdr);

		if (buf_len < ALIGN(board_ie_len, 4)) {
			ath10k_err(ar, "invalid ATH10K_BD_IE_BOARD length: %zu < %zu\n",
				   buf_len, ALIGN(board_ie_len, 4));
			ret = -EINVAL;
			goto out;
		}

		switch (board_ie_id) {
		case ATH10K_BD_IE_BOARD_NAME:
			ath10k_dbg_dump(ar, ATH10K_DBG_BOOT, "board name", "",
					board_ie_data, board_ie_len);

			if (board_ie_len != strlen(boardname))
				break;

			ret = memcmp(board_ie_data, boardname, strlen(boardname));
			if (ret)
				break;

			name_match_found = true;
			ath10k_dbg(ar, ATH10K_DBG_BOOT,
				   "boot found match for name '%s'",
				   boardname);
			break;
		case ATH10K_BD_IE_BOARD_DATA:
			if (!name_match_found)
				/* no match found */
				break;

			if (bd_ie_type == ATH10K_BD_IE_BOARD) {
				ath10k_dbg(ar, ATH10K_DBG_BOOT,
					   "boot found board data for '%s'",
						boardname);

				ar->normal_mode_fw.board_data = board_ie_data;
				ar->normal_mode_fw.board_len = board_ie_len;
			} else if (bd_ie_type == ATH10K_BD_IE_BOARD_EXT) {
				ath10k_dbg(ar, ATH10K_DBG_BOOT,
					   "boot found eboard data for '%s'",
						boardname);

				ar->normal_mode_fw.ext_board_data = board_ie_data;
				ar->normal_mode_fw.ext_board_len = board_ie_len;
			}

			ret = 0;
			goto out;
		default:
			ath10k_warn(ar, "unknown ATH10K_BD_IE_BOARD found: %d\n",
				    board_ie_id);
			break;
		}

		/* jump over the padding */
		board_ie_len = ALIGN(board_ie_len, 4);

		buf_len -= board_ie_len;
		buf += board_ie_len;
	}

	/* no match found */
	ret = -ENOENT;

out:
	return ret;
}