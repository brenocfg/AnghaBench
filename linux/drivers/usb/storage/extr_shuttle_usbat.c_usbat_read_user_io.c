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
struct us_data {int /*<<< orphan*/  recv_ctrl_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBAT_CMD_UIO ; 
 int /*<<< orphan*/  USBAT_UIO_READ ; 
 int usb_stor_ctrl_transfer (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,unsigned char) ; 

__attribute__((used)) static int usbat_read_user_io(struct us_data *us, unsigned char *data_flags)
{
	int result;

	result = usb_stor_ctrl_transfer(us,
		us->recv_ctrl_pipe,
		USBAT_CMD_UIO,
		0xC0,
		0,
		0,
		data_flags,
		USBAT_UIO_READ);

	usb_stor_dbg(us, "UIO register reads %02X\n", *data_flags);

	return result;
}