#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct us_data {int /*<<< orphan*/  srb; TYPE_3__* unusual_dev; TYPE_2__* pusb_dev; } ;
typedef  unsigned char bcdDevice ;
struct TYPE_6__ {int /*<<< orphan*/  productName; int /*<<< orphan*/  vendorName; } ;
struct TYPE_4__ {int /*<<< orphan*/  bcdDevice; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stor_set_xfer_buf (unsigned char*,unsigned int,int /*<<< orphan*/ ) ; 

void fill_inquiry_response(struct us_data *us, unsigned char *data,
		unsigned int data_len)
{
	if (data_len < 36) /* You lose. */
		return;

	memset(data+8, ' ', 28);
	if (data[0]&0x20) { /*
			     * USB device currently not connected. Return
			     * peripheral qualifier 001b ("...however, the
			     * physical device is not currently connected
			     * to this logical unit") and leave vendor and
			     * product identification empty. ("If the target
			     * does store some of the INQUIRY data on the
			     * device, it may return zeros or ASCII spaces
			     * (20h) in those fields until the data is
			     * available from the device.").
			     */
	} else {
		u16 bcdDevice = le16_to_cpu(us->pusb_dev->descriptor.bcdDevice);
		int n;

		n = strlen(us->unusual_dev->vendorName);
		memcpy(data+8, us->unusual_dev->vendorName, min(8, n));
		n = strlen(us->unusual_dev->productName);
		memcpy(data+16, us->unusual_dev->productName, min(16, n));

		data[32] = 0x30 + ((bcdDevice>>12) & 0x0F);
		data[33] = 0x30 + ((bcdDevice>>8) & 0x0F);
		data[34] = 0x30 + ((bcdDevice>>4) & 0x0F);
		data[35] = 0x30 + ((bcdDevice) & 0x0F);
	}

	usb_stor_set_xfer_buf(data, data_len, us->srb);
}