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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ath10k_usb_submit_ctrl_in (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ath10k_usb_submit_ctrl_out (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_usb_ctrl_msg_exchange(struct ath10k *ar,
					u8 req_val, u8 *req_buf, u32 req_len,
					u8 resp_val, u8 *resp_buf,
					u32 *resp_len)
{
	int ret;

	/* send command */
	ret = ath10k_usb_submit_ctrl_out(ar, req_val, 0, 0,
					 req_buf, req_len);
	if (ret)
		goto err;

	/* get response */
	if (resp_buf) {
		ret = ath10k_usb_submit_ctrl_in(ar, resp_val, 0, 0,
						resp_buf, *resp_len);
		if (ret)
			goto err;
	}

	return 0;
err:
	return ret;
}