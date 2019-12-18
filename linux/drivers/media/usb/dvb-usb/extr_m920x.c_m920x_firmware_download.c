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
struct usb_device {int dummy; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  M9206_CORE ; 
 int /*<<< orphan*/  M9206_FILTER ; 
 int /*<<< orphan*/  M9206_FW ; 
 int /*<<< orphan*/  M9206_FW_GO ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  deb (char*,...) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int m920x_read (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  m920x_write (struct usb_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m920x_firmware_download(struct usb_device *udev, const struct firmware *fw)
{
	u16 value, index, size;
	u8 *read, *buff;
	int i, pass, ret = 0;

	buff = kmalloc(65536, GFP_KERNEL);
	if (buff == NULL)
		return -ENOMEM;

	read = kmalloc(4, GFP_KERNEL);
	if (!read) {
		kfree(buff);
		return -ENOMEM;
	}

	if ((ret = m920x_read(udev, M9206_FILTER, 0x0, 0x8000, read, 4)) != 0)
		goto done;
	deb("%*ph\n", 4, read);

	if ((ret = m920x_read(udev, M9206_FW, 0x0, 0x0, read, 1)) != 0)
		goto done;
	deb("%x\n", read[0]);

	for (pass = 0; pass < 2; pass++) {
		for (i = 0; i + (sizeof(u16) * 3) < fw->size;) {
			value = get_unaligned_le16(fw->data + i);
			i += sizeof(u16);

			index = get_unaligned_le16(fw->data + i);
			i += sizeof(u16);

			size = get_unaligned_le16(fw->data + i);
			i += sizeof(u16);

			if (pass == 1) {
				/* Will stall if using fw->data ... */
				memcpy(buff, fw->data + i, size);

				ret = usb_control_msg(udev, usb_sndctrlpipe(udev,0),
						      M9206_FW,
						      USB_TYPE_VENDOR | USB_DIR_OUT,
						      value, index, buff, size, 20);
				if (ret != size) {
					deb("error while uploading fw!\n");
					ret = -EIO;
					goto done;
				}
				msleep(3);
			}
			i += size;
		}
		if (i != fw->size) {
			deb("bad firmware file!\n");
			ret = -EINVAL;
			goto done;
		}
	}

	msleep(36);

	/* m920x will disconnect itself from the bus after this. */
	(void) m920x_write(udev, M9206_CORE, 0x01, M9206_FW_GO);
	deb("firmware uploaded!\n");

 done:
	kfree(read);
	kfree(buff);

	return ret;
}