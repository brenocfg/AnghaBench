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
typedef  int u16 ;
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
#define  ADDR_B1A6_STREAM_CTRL 131 
#define  ADDR_B600_VOLTAGE_13V 130 
#define  ADDR_B601_VOLTAGE_18V 129 
#define  ADDR_B880_READ_REMOTE 128 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  OPERA_READ_MSG ; 
 int /*<<< orphan*/  OPERA_WRITE_MSG ; 
 int /*<<< orphan*/  info (char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int opera1_xilinx_rw (int /*<<< orphan*/ ,int,int,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opera1_usb_i2c_msgxfer(struct dvb_usb_device *dev, u16 addr,
				  u8 * buf, u16 len)
{
	int ret = 0;
	u8 request;
	u16 value;

	if (!dev) {
		info("no usb_device");
		return -EINVAL;
	}
	if (mutex_lock_interruptible(&dev->usb_mutex) < 0)
		return -EAGAIN;

	switch (addr>>1){
		case ADDR_B600_VOLTAGE_13V:
			request=0xb6;
			value=0x00;
			break;
		case ADDR_B601_VOLTAGE_18V:
			request=0xb6;
			value=0x01;
			break;
		case ADDR_B1A6_STREAM_CTRL:
			request=0xb1;
			value=0xa6;
			break;
		case ADDR_B880_READ_REMOTE:
			request=0xb8;
			value=0x80;
			break;
		default:
			request=0xb1;
			value=addr;
	}
	ret = opera1_xilinx_rw(dev->udev, request,
		value, buf, len,
		addr&0x01?OPERA_READ_MSG:OPERA_WRITE_MSG);

	mutex_unlock(&dev->usb_mutex);
	return ret;
}