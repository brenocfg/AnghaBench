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
typedef  int /*<<< orphan*/  u8 ;
struct ath10k_fw_ie {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
#define  ATH10K_BD_IE_BOARD 129 
#define  ATH10K_BD_IE_BOARD_EXT 128 
 int EINVAL ; 
 int ENOENT ; 
 int ath10k_core_parse_bd_ie_board (struct ath10k*,int /*<<< orphan*/  const*,size_t,char const*,int const) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int,size_t,size_t) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_core_search_bd(struct ath10k *ar,
				 const char *boardname,
				 const u8 *data,
				 size_t len)
{
	size_t ie_len;
	struct ath10k_fw_ie *hdr;
	int ret = -ENOENT, ie_id;

	while (len > sizeof(struct ath10k_fw_ie)) {
		hdr = (struct ath10k_fw_ie *)data;
		ie_id = le32_to_cpu(hdr->id);
		ie_len = le32_to_cpu(hdr->len);

		len -= sizeof(*hdr);
		data = hdr->data;

		if (len < ALIGN(ie_len, 4)) {
			ath10k_err(ar, "invalid length for board ie_id %d ie_len %zu len %zu\n",
				   ie_id, ie_len, len);
			return -EINVAL;
		}

		switch (ie_id) {
		case ATH10K_BD_IE_BOARD:
			ret = ath10k_core_parse_bd_ie_board(ar, data, ie_len,
							    boardname,
							    ATH10K_BD_IE_BOARD);
			if (ret == -ENOENT)
				/* no match found, continue */
				break;

			/* either found or error, so stop searching */
			goto out;
		case ATH10K_BD_IE_BOARD_EXT:
			ret = ath10k_core_parse_bd_ie_board(ar, data, ie_len,
							    boardname,
							    ATH10K_BD_IE_BOARD_EXT);
			if (ret == -ENOENT)
				/* no match found, continue */
				break;

			/* either found or error, so stop searching */
			goto out;
		}

		/* jump over the padding */
		ie_len = ALIGN(ie_len, 4);

		len -= ie_len;
		data += ie_len;
	}

out:
	/* return result of parse_bd_ie_board() or -ENOENT */
	return ret;
}