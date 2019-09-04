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
struct dvb_usb_device {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int dvbsky_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int) ; 

__attribute__((used)) static int dvbsky_ci_ctrl(void *priv, u8 read, int addr,
					u8 data, int *mem)
{
	struct dvb_usb_device *d = priv;
	int ret = 0;
	u8 command[4], respond[2], command_size, respond_size;

	command[1] = (u8)((addr >> 8) & 0xff); /*high part of address*/
	command[2] = (u8)(addr & 0xff); /*low part of address*/
	if (read) {
		command[0] = 0x71;
		command_size = 3;
		respond_size = 2;
	} else {
		command[0] = 0x70;
		command[3] = data;
		command_size = 4;
		respond_size = 1;
	}
	ret = dvbsky_usb_generic_rw(d, command, command_size,
			respond, respond_size);
	if (ret)
		goto err;
	if (read)
		*mem = respond[1];
	return ret;
err:
	dev_err(&d->udev->dev, "ci control failed=%d\n", ret);
	return ret;
}