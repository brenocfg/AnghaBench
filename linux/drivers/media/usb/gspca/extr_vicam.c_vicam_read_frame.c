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
typedef  int u8 ;
struct TYPE_2__ {int width; int height; } ;
struct gspca_dev {int* usb_buf; int /*<<< orphan*/  dev; int /*<<< orphan*/  usb_lock; TYPE_1__ pixfmt; int /*<<< orphan*/  gain; int /*<<< orphan*/  exposure; } ;
typedef  int s32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 int vicam_control_msg (struct gspca_dev*,int,int,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int vicam_read_frame(struct gspca_dev *gspca_dev, u8 *data, int size)
{
	int ret, unscaled_height, act_len = 0;
	u8 *req_data = gspca_dev->usb_buf;
	s32 expo = v4l2_ctrl_g_ctrl(gspca_dev->exposure);
	s32 gain = v4l2_ctrl_g_ctrl(gspca_dev->gain);

	memset(req_data, 0, 16);
	req_data[0] = gain;
	if (gspca_dev->pixfmt.width == 256)
		req_data[1] |= 0x01; /* low nibble x-scale */
	if (gspca_dev->pixfmt.height <= 122) {
		req_data[1] |= 0x10; /* high nibble y-scale */
		unscaled_height = gspca_dev->pixfmt.height * 2;
	} else
		unscaled_height = gspca_dev->pixfmt.height;
	req_data[2] = 0x90; /* unknown, does not seem to do anything */
	if (unscaled_height <= 200)
		req_data[3] = 0x06; /* vend? */
	else if (unscaled_height <= 242) /* Yes 242 not 240 */
		req_data[3] = 0x07; /* vend? */
	else /* Up to 244 lines with req_data[3] == 0x08 */
		req_data[3] = 0x08; /* vend? */

	if (expo < 256) {
		/* Frame rate maxed out, use partial frame expo time */
		req_data[4] = 255 - expo;
		req_data[5] = 0x00;
		req_data[6] = 0x00;
		req_data[7] = 0x01;
	} else {
		/* Modify frame rate */
		req_data[4] = 0x00;
		req_data[5] = 0x00;
		req_data[6] = expo & 0xFF;
		req_data[7] = expo >> 8;
	}
	req_data[8] = ((244 - unscaled_height) / 2) & ~0x01; /* vstart */
	/* bytes 9-15 do not seem to affect exposure or image quality */

	mutex_lock(&gspca_dev->usb_lock);
	ret = vicam_control_msg(gspca_dev, 0x51, 0x80, 0, req_data, 16);
	mutex_unlock(&gspca_dev->usb_lock);
	if (ret < 0)
		return ret;

	ret = usb_bulk_msg(gspca_dev->dev,
			   usb_rcvbulkpipe(gspca_dev->dev, 0x81),
			   data, size, &act_len, 10000);
	/* successful, it returns 0, otherwise  negative */
	if (ret < 0 || act_len != size) {
		pr_err("bulk read fail (%d) len %d/%d\n",
		       ret, act_len, size);
		return -EIO;
	}
	return 0;
}