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
typedef  scalar_t__ u16 ;
struct rtsx_ucr {scalar_t__ cmd_buf; int /*<<< orphan*/  pusb_dev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  EP_BULK_OUT ; 
 scalar_t__ IOBUF_SIZE ; 
 int /*<<< orphan*/  SEQ_WRITE ; 
 scalar_t__ SEQ_WRITE_DATA_OFFSET ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rtsx_usb_seq_cmd_hdr (struct rtsx_ucr*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int rtsx_usb_transfer_data (struct rtsx_ucr*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtsx_usb_seq_write_register(struct rtsx_ucr *ucr,
		u16 addr, u16 len, u8 *data)
{
	u16 cmd_len = ALIGN(SEQ_WRITE_DATA_OFFSET + len, 4);

	if (!data)
		return -EINVAL;

	if (cmd_len > IOBUF_SIZE)
		return -EINVAL;

	rtsx_usb_seq_cmd_hdr(ucr, addr, len, SEQ_WRITE);
	memcpy(ucr->cmd_buf + SEQ_WRITE_DATA_OFFSET, data, len);

	return rtsx_usb_transfer_data(ucr,
			usb_sndbulkpipe(ucr->pusb_dev, EP_BULK_OUT),
			ucr->cmd_buf, cmd_len, 0, NULL, 100);
}