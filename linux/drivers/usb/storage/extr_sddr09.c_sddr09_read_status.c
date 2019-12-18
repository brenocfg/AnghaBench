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
struct us_data {unsigned char* iobuf; int /*<<< orphan*/  recv_bulk_pipe; } ;

/* Variables and functions */
 int EIO ; 
 unsigned char LUNBITS ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int sddr09_send_scsi_command (struct us_data*,unsigned char*,int) ; 
 int usb_stor_bulk_transfer_buf (struct us_data*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*) ; 

__attribute__((used)) static int
sddr09_read_status(struct us_data *us, unsigned char *status) {

	unsigned char *command = us->iobuf;
	unsigned char *data = us->iobuf;
	int result;

	usb_stor_dbg(us, "Reading status...\n");

	memset(command, 0, 12);
	command[0] = 0xEC;
	command[1] = LUNBITS;

	result = sddr09_send_scsi_command(us, command, 12);
	if (result)
		return result;

	result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
				       data, 64, NULL);
	*status = data[0];
	return (result == USB_STOR_XFER_GOOD ? 0 : -EIO);
}