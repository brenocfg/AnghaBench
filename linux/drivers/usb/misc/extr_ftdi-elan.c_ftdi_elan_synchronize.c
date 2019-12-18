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
struct usb_ftdi {int bulk_in_last; char* bulk_in_buffer; TYPE_1__* udev; int /*<<< orphan*/  bulk_in_size; int /*<<< orphan*/  bulk_in_endpointAddr; scalar_t__ bulk_in_left; } ;
typedef  int /*<<< orphan*/  diag ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int ftdi_elan_flush_input_fifo (struct usb_ftdi*) ; 
 int ftdi_elan_synchronize_flush (struct usb_ftdi*) ; 
 int ftdi_elan_synchronize_reset (struct usb_ftdi*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int usb_bulk_msg (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftdi_elan_synchronize(struct usb_ftdi *ftdi)
{
	int retval;
	int long_stop = 10;
	int retry_on_timeout = 5;
	int retry_on_empty = 10;
	int err_count = 0;
	retval = ftdi_elan_flush_input_fifo(ftdi);
	if (retval)
		return retval;
	ftdi->bulk_in_left = 0;
	ftdi->bulk_in_last = -1;
	while (long_stop-- > 0) {
		int read_stop;
		int read_stuck;
		retval = ftdi_elan_synchronize_flush(ftdi);
		if (retval)
			return retval;
		retval = ftdi_elan_flush_input_fifo(ftdi);
		if (retval)
			return retval;
	reset:retval = ftdi_elan_synchronize_reset(ftdi);
		if (retval)
			return retval;
		read_stop = 100;
		read_stuck = 10;
	read:{
			int packet_bytes = 0;
			retval = usb_bulk_msg(ftdi->udev,
					      usb_rcvbulkpipe(ftdi->udev,
							      ftdi->bulk_in_endpointAddr),
					      ftdi->bulk_in_buffer, ftdi->bulk_in_size,
					      &packet_bytes, 500);
			if (packet_bytes > 2) {
				char diag[30 *3 + 4];
				char *d = diag;
				int m = (sizeof(diag) - 1) / 3 - 1;
				char *b = ftdi->bulk_in_buffer;
				int bytes_read = 0;
				unsigned char c = 0;
				diag[0] = 0;
				while (packet_bytes-- > 0) {
					c = *b++;
					if (bytes_read < m) {
						d += sprintf(d, " %02X", c);
					} else if (bytes_read > m) {
					} else
						d += sprintf(d, " ..");
					bytes_read += 1;
					continue;
				}
				if (c == 0x7E) {
					return 0;
				} else {
					if (c == 0x55) {
						goto read;
					} else if (read_stop-- > 0) {
						goto read;
					} else {
						dev_err(&ftdi->udev->dev, "retry limit reached\n");
						continue;
					}
				}
			} else if (packet_bytes > 1) {
				unsigned char s1 = ftdi->bulk_in_buffer[0];
				unsigned char s2 = ftdi->bulk_in_buffer[1];
				if (s1 == 0x31 && s2 == 0x00) {
					if (read_stuck-- > 0) {
						goto read;
					} else
						goto reset;
				} else {
					if (read_stop-- > 0) {
						goto read;
					} else {
						dev_err(&ftdi->udev->dev, "retry limit reached\n");
						continue;
					}
				}
			} else if (packet_bytes > 0) {
				if (read_stop-- > 0) {
					goto read;
				} else {
					dev_err(&ftdi->udev->dev, "retry limit reached\n");
					continue;
				}
			} else if (retval == -ETIMEDOUT) {
				if (retry_on_timeout-- > 0) {
					goto read;
				} else {
					dev_err(&ftdi->udev->dev, "TIMED OUT retry limit reached\n");
					continue;
				}
			} else if (retval == 0) {
				if (retry_on_empty-- > 0) {
					goto read;
				} else {
					dev_err(&ftdi->udev->dev, "empty packet retry limit reached\n");
					continue;
				}
			} else {
				err_count += 1;
				dev_err(&ftdi->udev->dev, "error = %d\n",
					retval);
				if (read_stop-- > 0) {
					goto read;
				} else {
					dev_err(&ftdi->udev->dev, "retry limit reached\n");
					continue;
				}
			}
		}
	}
	dev_err(&ftdi->udev->dev, "failed to synchronize\n");
	return -EFAULT;
}