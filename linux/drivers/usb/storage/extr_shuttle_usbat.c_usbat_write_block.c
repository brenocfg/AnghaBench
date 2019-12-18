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
struct us_data {unsigned char* iobuf; } ;

/* Variables and functions */
 unsigned char LSB_of (unsigned short) ; 
 unsigned char MSB_of (unsigned short) ; 
 unsigned char USBAT_ATA_DATA ; 
 unsigned char USBAT_CMD_WRITE_BLOCK ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int usbat_bulk_write (struct us_data*,void*,unsigned short,int) ; 
 int usbat_execute_command (struct us_data*,unsigned char*,int) ; 
 int usbat_wait_not_busy (struct us_data*,int) ; 

__attribute__((used)) static int usbat_write_block(struct us_data *us,
			     unsigned char access,
			     void* buf,
			     unsigned short len,
			     int minutes,
			     int use_sg)
{
	int result;
	unsigned char *command = us->iobuf;

	if (!len)
		return USB_STOR_TRANSPORT_GOOD;

	command[0] = 0x40;
	command[1] = access | USBAT_CMD_WRITE_BLOCK;
	command[2] = USBAT_ATA_DATA;
	command[3] = 0;
	command[4] = 0;
	command[5] = 0;
	command[6] = LSB_of(len);
	command[7] = MSB_of(len);

	result = usbat_execute_command(us, command, 8);

	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	result = usbat_bulk_write(us, buf, len, use_sg);
	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	return usbat_wait_not_busy(us, minutes);
}