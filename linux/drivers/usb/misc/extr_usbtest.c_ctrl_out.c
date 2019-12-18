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
struct usbtest_dev {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR (struct usbtest_dev*,char*,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ realworld ; 
 struct usb_device* testdev_to_usbdev (struct usbtest_dev*) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctrl_out(struct usbtest_dev *dev,
		unsigned count, unsigned length, unsigned vary, unsigned offset)
{
	unsigned		i, j, len;
	int			retval;
	u8			*buf;
	char			*what = "?";
	struct usb_device	*udev;

	if (length < 1 || length > 0xffff || vary >= length)
		return -EINVAL;

	buf = kmalloc(length + offset, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf += offset;
	udev = testdev_to_usbdev(dev);
	len = length;
	retval = 0;

	/* NOTE:  hardware might well act differently if we pushed it
	 * with lots back-to-back queued requests.
	 */
	for (i = 0; i < count; i++) {
		/* write patterned data */
		for (j = 0; j < len; j++)
			buf[j] = (u8)(i + j);
		retval = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				0x5b, USB_DIR_OUT|USB_TYPE_VENDOR,
				0, 0, buf, len, USB_CTRL_SET_TIMEOUT);
		if (retval != len) {
			what = "write";
			if (retval >= 0) {
				ERROR(dev, "ctrl_out, wlen %d (expected %d)\n",
						retval, len);
				retval = -EBADMSG;
			}
			break;
		}

		/* read it back -- assuming nothing intervened!!  */
		retval = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				0x5c, USB_DIR_IN|USB_TYPE_VENDOR,
				0, 0, buf, len, USB_CTRL_GET_TIMEOUT);
		if (retval != len) {
			what = "read";
			if (retval >= 0) {
				ERROR(dev, "ctrl_out, rlen %d (expected %d)\n",
						retval, len);
				retval = -EBADMSG;
			}
			break;
		}

		/* fail if we can't verify */
		for (j = 0; j < len; j++) {
			if (buf[j] != (u8)(i + j)) {
				ERROR(dev, "ctrl_out, byte %d is %d not %d\n",
					j, buf[j], (u8)(i + j));
				retval = -EBADMSG;
				break;
			}
		}
		if (retval < 0) {
			what = "verify";
			break;
		}

		len += vary;

		/* [real world] the "zero bytes IN" case isn't really used.
		 * hardware can easily trip up in this weird case, since its
		 * status stage is IN, not OUT like other ep0in transfers.
		 */
		if (len > length)
			len = realworld ? 1 : 0;
	}

	if (retval < 0)
		ERROR(dev, "ctrl_out %s failed, code %d, count %d\n",
			what, retval, i);

	kfree(buf - offset);
	return retval;
}