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
typedef  int u8 ;
struct usb_serial {int /*<<< orphan*/  dev; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIO_REGISTER ; 
 int /*<<< orphan*/  MCS_RDREQ ; 
 int /*<<< orphan*/  MCS_RD_RTYPE ; 
 int /*<<< orphan*/  MCS_WRREQ ; 
 int /*<<< orphan*/  MCS_WR_RTYPE ; 
 int /*<<< orphan*/  MODEM_CONTROL_REGISTER ; 
 int /*<<< orphan*/  MOS_WDR_TIMEOUT ; 
 int VENDOR_READ_LENGTH ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mos7810_check(struct usb_serial *serial)
{
	int i, pass_count = 0;
	u8 *buf;
	__u16 data = 0, mcr_data = 0;
	__u16 test_pattern = 0x55AA;
	int res;

	buf = kmalloc(VENDOR_READ_LENGTH, GFP_KERNEL);
	if (!buf)
		return 0;	/* failed to identify 7810 */

	/* Store MCR setting */
	res = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
		MCS_RDREQ, MCS_RD_RTYPE, 0x0300, MODEM_CONTROL_REGISTER,
		buf, VENDOR_READ_LENGTH, MOS_WDR_TIMEOUT);
	if (res == VENDOR_READ_LENGTH)
		mcr_data = *buf;

	for (i = 0; i < 16; i++) {
		/* Send the 1-bit test pattern out to MCS7810 test pin */
		usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			MCS_WRREQ, MCS_WR_RTYPE,
			(0x0300 | (((test_pattern >> i) & 0x0001) << 1)),
			MODEM_CONTROL_REGISTER, NULL, 0, MOS_WDR_TIMEOUT);

		/* Read the test pattern back */
		res = usb_control_msg(serial->dev,
				usb_rcvctrlpipe(serial->dev, 0), MCS_RDREQ,
				MCS_RD_RTYPE, 0, GPIO_REGISTER, buf,
				VENDOR_READ_LENGTH, MOS_WDR_TIMEOUT);
		if (res == VENDOR_READ_LENGTH)
			data = *buf;

		/* If this is a MCS7810 device, both test patterns must match */
		if (((test_pattern >> i) ^ (~data >> 1)) & 0x0001)
			break;

		pass_count++;
	}

	/* Restore MCR setting */
	usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0), MCS_WRREQ,
		MCS_WR_RTYPE, 0x0300 | mcr_data, MODEM_CONTROL_REGISTER, NULL,
		0, MOS_WDR_TIMEOUT);

	kfree(buf);

	if (pass_count == 16)
		return 1;

	return 0;
}