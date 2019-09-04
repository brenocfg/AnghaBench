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
typedef  void* u8 ;
struct rtsx_ucr {int cmd_idx; void** cmd_buf; int /*<<< orphan*/  pusb_dev; } ;

/* Variables and functions */
 scalar_t__ CMD_OFFSET ; 
 size_t CNT_H ; 
 size_t CNT_L ; 
 int /*<<< orphan*/  EP_BULK_OUT ; 
 size_t STAGE_FLAG ; 
 int /*<<< orphan*/  rtsx_usb_clear_fsm_err (struct rtsx_ucr*) ; 
 int rtsx_usb_transfer_data (struct rtsx_ucr*,int /*<<< orphan*/ ,void**,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtsx_usb_send_cmd(struct rtsx_ucr *ucr, u8 flag, int timeout)
{
	int ret;

	ucr->cmd_buf[CNT_H] = (u8)(ucr->cmd_idx >> 8);
	ucr->cmd_buf[CNT_L] = (u8)(ucr->cmd_idx);
	ucr->cmd_buf[STAGE_FLAG] = flag;

	ret = rtsx_usb_transfer_data(ucr,
			usb_sndbulkpipe(ucr->pusb_dev, EP_BULK_OUT),
			ucr->cmd_buf, ucr->cmd_idx * 4 + CMD_OFFSET,
			0, NULL, timeout);
	if (ret) {
		rtsx_usb_clear_fsm_err(ucr);
		return ret;
	}

	return 0;
}