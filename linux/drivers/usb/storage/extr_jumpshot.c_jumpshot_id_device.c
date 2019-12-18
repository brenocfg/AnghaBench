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
typedef  int u32 ;
struct us_data {unsigned char* iobuf; int /*<<< orphan*/  send_ctrl_pipe; } ;
struct jumpshot_info {int sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int jumpshot_bulk_read (struct us_data*,unsigned char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_stor_ctrl_transfer (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*) ; 

__attribute__((used)) static int jumpshot_id_device(struct us_data *us,
			      struct jumpshot_info *info)
{
	unsigned char *command = us->iobuf;
	unsigned char *reply;
	int 	 rc;

	if (!info)
		return USB_STOR_TRANSPORT_ERROR;

	command[0] = 0xE0;
	command[1] = 0xEC;
	reply = kmalloc(512, GFP_NOIO);
	if (!reply)
		return USB_STOR_TRANSPORT_ERROR;

	// send the setup
	rc = usb_stor_ctrl_transfer(us, us->send_ctrl_pipe,
				   0, 0x20, 0, 6, command, 2);

	if (rc != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Gah! send_control for read_capacity failed\n");
		rc = USB_STOR_TRANSPORT_ERROR;
		goto leave;
	}

	// read the reply
	rc = jumpshot_bulk_read(us, reply, 512);
	if (rc != USB_STOR_XFER_GOOD) {
		rc = USB_STOR_TRANSPORT_ERROR;
		goto leave;
	}

	info->sectors = ((u32)(reply[117]) << 24) |
			((u32)(reply[116]) << 16) |
			((u32)(reply[115]) <<  8) |
			((u32)(reply[114])      );

	rc = USB_STOR_TRANSPORT_GOOD;

 leave:
	kfree(reply);
	return rc;
}