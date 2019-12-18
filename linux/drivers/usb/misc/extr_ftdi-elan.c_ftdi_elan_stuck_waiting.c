#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_ftdi {char* bulk_in_buffer; TYPE_1__* udev; int /*<<< orphan*/  bulk_in_size; int /*<<< orphan*/  bulk_in_endpointAddr; } ;
typedef  int /*<<< orphan*/  diag ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int usb_bulk_msg (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftdi_elan_stuck_waiting(struct usb_ftdi *ftdi)
{
	int retry_on_empty = 10;
	int retry_on_timeout = 5;
	int retry_on_status = 50;
more:{
		int packet_bytes = 0;
		int retval = usb_bulk_msg(ftdi->udev,
					  usb_rcvbulkpipe(ftdi->udev, ftdi->bulk_in_endpointAddr),
					  ftdi->bulk_in_buffer, ftdi->bulk_in_size,
					  &packet_bytes, 1000);
		if (packet_bytes > 2) {
			char diag[30 *3 + 4];
			char *d = diag;
			int m = (sizeof(diag) - 1) / 3 - 1;
			char *b = ftdi->bulk_in_buffer;
			int bytes_read = 0;
			diag[0] = 0;
			while (packet_bytes-- > 0) {
				char c = *b++;
				if (bytes_read < m) {
					d += sprintf(d, " %02X",
						     0x000000FF & c);
				} else if (bytes_read > m) {
				} else
					d += sprintf(d, " ..");
				bytes_read += 1;
				continue;
			}
			goto more;
		} else if (packet_bytes > 1) {
			char s1 = ftdi->bulk_in_buffer[0];
			char s2 = ftdi->bulk_in_buffer[1];
			if (s1 == 0x31 && s2 == 0x60) {
				return 0;
			} else if (retry_on_status-- > 0) {
				msleep(5);
				goto more;
			} else
				return -EFAULT;
		} else if (packet_bytes > 0) {
			char b1 = ftdi->bulk_in_buffer[0];
			dev_err(&ftdi->udev->dev, "only one byte flushed from FTDI = %02X\n", b1);
			if (retry_on_status-- > 0) {
				msleep(5);
				goto more;
			} else {
				dev_err(&ftdi->udev->dev, "STATUS ERROR retry limit reached\n");
				return -EFAULT;
			}
		} else if (retval == -ETIMEDOUT) {
			if (retry_on_timeout-- > 0) {
				goto more;
			} else {
				dev_err(&ftdi->udev->dev, "TIMED OUT retry limit reached\n");
				return -ENOMEM;
			}
		} else if (retval == 0) {
			if (retry_on_empty-- > 0) {
				goto more;
			} else {
				dev_err(&ftdi->udev->dev, "empty packet retry limit reached\n");
				return -ENOMEM;
			}
		} else {
			dev_err(&ftdi->udev->dev, "error = %d\n", retval);
			return -ENOMEM;
		}
	}
	return -1;
}