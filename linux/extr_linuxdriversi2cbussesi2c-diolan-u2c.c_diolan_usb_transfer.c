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
struct i2c_diolan_u2c {int olen; int ocount; int* obuffer; int* ibuffer; int /*<<< orphan*/  ep_in; int /*<<< orphan*/  usb_dev; int /*<<< orphan*/  ep_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOLAN_USB_TIMEOUT ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
#define  RESP_NACK 130 
#define  RESP_OK 129 
#define  RESP_TIMEOUT 128 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diolan_usb_transfer(struct i2c_diolan_u2c *dev)
{
	int ret = 0;
	int actual;
	int i;

	if (!dev->olen || !dev->ocount)
		return -EINVAL;

	ret = usb_bulk_msg(dev->usb_dev,
			   usb_sndbulkpipe(dev->usb_dev, dev->ep_out),
			   dev->obuffer, dev->olen, &actual,
			   DIOLAN_USB_TIMEOUT);
	if (!ret) {
		for (i = 0; i < dev->ocount; i++) {
			int tmpret;

			tmpret = usb_bulk_msg(dev->usb_dev,
					      usb_rcvbulkpipe(dev->usb_dev,
							      dev->ep_in),
					      dev->ibuffer,
					      sizeof(dev->ibuffer), &actual,
					      DIOLAN_USB_TIMEOUT);
			/*
			 * Stop command processing if a previous command
			 * returned an error.
			 * Note that we still need to retrieve all messages.
			 */
			if (ret < 0)
				continue;
			ret = tmpret;
			if (ret == 0 && actual > 0) {
				switch (dev->ibuffer[actual - 1]) {
				case RESP_NACK:
					/*
					 * Return ENXIO if NACK was received as
					 * response to the address phase,
					 * EIO otherwise
					 */
					ret = i == 1 ? -ENXIO : -EIO;
					break;
				case RESP_TIMEOUT:
					ret = -ETIMEDOUT;
					break;
				case RESP_OK:
					/* strip off return code */
					ret = actual - 1;
					break;
				default:
					ret = -EIO;
					break;
				}
			}
		}
	}
	dev->olen = 0;
	dev->ocount = 0;
	return ret;
}