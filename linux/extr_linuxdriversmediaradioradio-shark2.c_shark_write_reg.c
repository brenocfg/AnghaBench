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
typedef  int u64 ;
struct shark_device {int* transfer_buffer; int /*<<< orphan*/  usbdev; } ;
struct radio_tea5777 {int /*<<< orphan*/  v4l2_dev; struct shark_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHARK_OUT_EP ; 
 int /*<<< orphan*/  TB_LEN ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_interrupt_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int shark_write_reg(struct radio_tea5777 *tea, u64 reg)
{
	struct shark_device *shark = tea->private_data;
	int i, res, actual_len;

	memset(shark->transfer_buffer, 0, TB_LEN);
	shark->transfer_buffer[0] = 0x81; /* Write register command */
	for (i = 0; i < 6; i++)
		shark->transfer_buffer[i + 1] = (reg >> (40 - i * 8)) & 0xff;

	v4l2_dbg(1, debug, tea->v4l2_dev, "shark2-write: %*ph\n",
		 7, shark->transfer_buffer);

	res = usb_interrupt_msg(shark->usbdev,
				usb_sndintpipe(shark->usbdev, SHARK_OUT_EP),
				shark->transfer_buffer, TB_LEN,
				&actual_len, 1000);
	if (res < 0) {
		v4l2_err(tea->v4l2_dev, "write error: %d\n", res);
		return res;
	}

	return 0;
}