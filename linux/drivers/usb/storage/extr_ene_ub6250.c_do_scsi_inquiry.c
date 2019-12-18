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
struct us_data {int dummy; } ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  usb_stor_set_xfer_buf (unsigned char*,int,struct scsi_cmnd*) ; 

__attribute__((used)) static int do_scsi_inquiry(struct us_data *us, struct scsi_cmnd *srb)
{
	unsigned char data_ptr[36] = {
		0x00, 0x00, 0x02, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x55,
		0x53, 0x42, 0x32, 0x2E, 0x30, 0x20, 0x20, 0x43, 0x61,
		0x72, 0x64, 0x52, 0x65, 0x61, 0x64, 0x65, 0x72, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x31, 0x30, 0x30 };

	usb_stor_set_xfer_buf(data_ptr, 36, srb);
	return USB_STOR_TRANSPORT_GOOD;
}