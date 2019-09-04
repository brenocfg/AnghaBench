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
typedef  int u32 ;
struct snd_tea575x {struct shark_device* private_data; } ;
struct TYPE_2__ {int stereo; } ;
struct shark_device {int* transfer_buffer; int last_val; TYPE_1__ tea; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHARK_IN_EP ; 
 int /*<<< orphan*/  SHARK_OUT_EP ; 
 int /*<<< orphan*/  TB_LEN ; 
 int TEA575X_BIT_BAND_FM ; 
 int TEA575X_BIT_BAND_MASK ; 
 int TEA575X_BIT_MONO ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_interrupt_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static u32 shark_read_val(struct snd_tea575x *tea)
{
	struct shark_device *shark = tea->private_data;
	int i, res, actual_len;
	u32 val = 0;

	memset(shark->transfer_buffer, 0, TB_LEN);
	shark->transfer_buffer[0] = 0x80;
	res = usb_interrupt_msg(shark->usbdev,
				usb_sndintpipe(shark->usbdev, SHARK_OUT_EP),
				shark->transfer_buffer, TB_LEN,
				&actual_len, 1000);
	if (res < 0) {
		v4l2_err(&shark->v4l2_dev, "request-status error: %d\n", res);
		return shark->last_val;
	}

	res = usb_interrupt_msg(shark->usbdev,
				usb_rcvintpipe(shark->usbdev, SHARK_IN_EP),
				shark->transfer_buffer, TB_LEN,
				&actual_len, 1000);
	if (res < 0) {
		v4l2_err(&shark->v4l2_dev, "get-status error: %d\n", res);
		return shark->last_val;
	}

	for (i = 0; i < 4; i++)
		val |= shark->transfer_buffer[i] << (24 - i * 8);

	shark->last_val = val;

	/*
	 * The shark does not allow actually reading the stereo / mono pin :(
	 * So assume that when we're tuned to an FM station and mono has not
	 * been requested, that we're receiving stereo.
	 */
	if (((val & TEA575X_BIT_BAND_MASK) == TEA575X_BIT_BAND_FM) &&
	    !(val & TEA575X_BIT_MONO))
		shark->tea.stereo = true;
	else
		shark->tea.stereo = false;

	return val;
}