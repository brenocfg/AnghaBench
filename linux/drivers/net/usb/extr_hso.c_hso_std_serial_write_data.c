#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hso_serial {int tx_data_count; TYPE_2__* parent; int /*<<< orphan*/  tx_urb; int /*<<< orphan*/  tx_data; TYPE_1__* out_endp; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_3__* usb; } ;
struct TYPE_5__ {int bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hso_std_serial_write_bulk_callback ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct hso_serial*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_3__*,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hso_std_serial_write_data(struct hso_serial *serial)
{
	int count = serial->tx_data_count;
	int result;

	usb_fill_bulk_urb(serial->tx_urb,
			  serial->parent->usb,
			  usb_sndbulkpipe(serial->parent->usb,
					  serial->out_endp->
					  bEndpointAddress & 0x7F),
			  serial->tx_data, serial->tx_data_count,
			  hso_std_serial_write_bulk_callback, serial);

	result = usb_submit_urb(serial->tx_urb, GFP_ATOMIC);
	if (result) {
		dev_warn(&serial->parent->usb->dev,
			 "Failed to submit urb - res %d\n", result);
		return result;
	}

	return count;
}