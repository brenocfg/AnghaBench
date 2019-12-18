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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  tx_len ;
struct TYPE_2__ {scalar_t__ const max_data_size; scalar_t__ const max_cmd_size; scalar_t__* cmd_buf; scalar_t__ done_sent; } ;
struct ath6kl {TYPE_1__ bmi; } ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  cid ;
typedef  int /*<<< orphan*/  aligned_buf ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BMI ; 
 scalar_t__ BMI_WRITE_MEMORY ; 
 int E2BIG ; 
 int EACCES ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int ath6kl_hif_bmi_write (struct ath6kl*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,scalar_t__ const) ; 

int ath6kl_bmi_write(struct ath6kl *ar, u32 addr, u8 *buf, u32 len)
{
	u32 cid = BMI_WRITE_MEMORY;
	int ret;
	u32 offset;
	u32 len_remain, tx_len;
	const u32 header = sizeof(cid) + sizeof(addr) + sizeof(len);
	u8 aligned_buf[400];
	u8 *src;

	if (ar->bmi.done_sent) {
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		return -EACCES;
	}

	if ((ar->bmi.max_data_size + header) > ar->bmi.max_cmd_size) {
		WARN_ON(1);
		return -EINVAL;
	}

	if (WARN_ON(ar->bmi.max_data_size > sizeof(aligned_buf)))
		return -E2BIG;

	memset(ar->bmi.cmd_buf, 0, ar->bmi.max_data_size + header);

	ath6kl_dbg(ATH6KL_DBG_BMI,
		   "bmi write memory: addr: 0x%x, len: %d\n", addr, len);

	len_remain = len;
	while (len_remain) {
		src = &buf[len - len_remain];

		if (len_remain < (ar->bmi.max_data_size - header)) {
			if (len_remain & 3) {
				/* align it with 4 bytes */
				len_remain = len_remain +
					     (4 - (len_remain & 3));
				memcpy(aligned_buf, src, len_remain);
				src = aligned_buf;
			}
			tx_len = len_remain;
		} else {
			tx_len = (ar->bmi.max_data_size - header);
		}

		offset = 0;
		memcpy(&(ar->bmi.cmd_buf[offset]), &cid, sizeof(cid));
		offset += sizeof(cid);
		memcpy(&(ar->bmi.cmd_buf[offset]), &addr, sizeof(addr));
		offset += sizeof(addr);
		memcpy(&(ar->bmi.cmd_buf[offset]), &tx_len, sizeof(tx_len));
		offset += sizeof(tx_len);
		memcpy(&(ar->bmi.cmd_buf[offset]), src, tx_len);
		offset += tx_len;

		ret = ath6kl_hif_bmi_write(ar, ar->bmi.cmd_buf, offset);
		if (ret) {
			ath6kl_err("Unable to write to the device: %d\n",
				   ret);
			return ret;
		}
		len_remain -= tx_len; addr += tx_len;
	}

	return 0;
}