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
typedef  int u16 ;
struct rtsx_ucr {int /*<<< orphan*/  pusb_dev; int /*<<< orphan*/ * cmd_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EP_BULK_IN ; 
 int /*<<< orphan*/  EP_BULK_OUT ; 
 int /*<<< orphan*/  SEQ_READ ; 
 int round_down (int,int) ; 
 int rtsx_usb_read_register (struct rtsx_ucr*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtsx_usb_seq_cmd_hdr (struct rtsx_ucr*,int,int,int /*<<< orphan*/ ) ; 
 int rtsx_usb_transfer_data (struct rtsx_ucr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtsx_usb_seq_read_register(struct rtsx_ucr *ucr,
		u16 addr, u16 len, u8 *data)
{
	int i, ret;
	u16 rsp_len = round_down(len, 4);
	u16 res_len = len - rsp_len;

	if (!data)
		return -EINVAL;

	/* 4-byte aligned part */
	if (rsp_len) {
		rtsx_usb_seq_cmd_hdr(ucr, addr, len, SEQ_READ);
		ret = rtsx_usb_transfer_data(ucr,
				usb_sndbulkpipe(ucr->pusb_dev, EP_BULK_OUT),
				ucr->cmd_buf, 12, 0, NULL, 100);
		if (ret)
			return ret;

		ret = rtsx_usb_transfer_data(ucr,
				usb_rcvbulkpipe(ucr->pusb_dev, EP_BULK_IN),
				data, rsp_len, 0, NULL, 100);
		if (ret)
			return ret;
	}

	/* unaligned part */
	for (i = 0; i < res_len; i++) {
		ret = rtsx_usb_read_register(ucr, addr + rsp_len + i,
				data + rsp_len + i);
		if (ret)
			return ret;
	}

	return 0;
}