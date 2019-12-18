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
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int ttusb2_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int tt3650_ci_msg(struct dvb_usb_device *d, u8 cmd, u8 *data, unsigned int write_len, unsigned int read_len)
{
	int ret;
	u8 rx[60];/* (64 -4) */
	ret = ttusb2_msg(d, cmd, data, write_len, rx, read_len);
	if (!ret)
		memcpy(data, rx, read_len);
	return ret;
}