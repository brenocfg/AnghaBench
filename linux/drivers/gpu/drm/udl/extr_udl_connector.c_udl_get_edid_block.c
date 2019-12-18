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
struct udl_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 unsigned int EDID_LENGTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udl_get_edid_block(void *data, u8 *buf, unsigned int block,
			       size_t len)
{
	int ret, i;
	u8 *read_buff;
	struct udl_device *udl = data;

	read_buff = kmalloc(2, GFP_KERNEL);
	if (!read_buff)
		return -1;

	for (i = 0; i < len; i++) {
		int bval = (i + block * EDID_LENGTH) << 8;
		ret = usb_control_msg(udl->udev,
				      usb_rcvctrlpipe(udl->udev, 0),
					  (0x02), (0x80 | (0x02 << 5)), bval,
					  0xA1, read_buff, 2, HZ);
		if (ret < 1) {
			DRM_ERROR("Read EDID byte %d failed err %x\n", i, ret);
			kfree(read_buff);
			return -1;
		}
		buf[i] = read_buff[1];
	}

	kfree(read_buff);
	return 0;
}