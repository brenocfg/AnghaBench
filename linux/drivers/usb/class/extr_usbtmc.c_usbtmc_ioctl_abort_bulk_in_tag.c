#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usbtmc_device_data {int /*<<< orphan*/  bulk_in; int /*<<< orphan*/  usb_dev; TYPE_1__* intf; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int ENOMSG ; 
 int EPERM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int USBTMC_BUFSIZE ; 
 int USBTMC_MAX_READS_TO_CLEAR_BULK_IN ; 
 int /*<<< orphan*/  USBTMC_REQUEST_CHECK_ABORT_BULK_IN_STATUS ; 
 int /*<<< orphan*/  USBTMC_REQUEST_INITIATE_ABORT_BULK_IN ; 
 int USBTMC_STATUS_FAILED ; 
 int USBTMC_STATUS_PENDING ; 
 int USBTMC_STATUS_SUCCESS ; 
 int USBTMC_STATUS_TRANSFER_NOT_IN_PROGRESS ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,int*,int,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbtmc_ioctl_abort_bulk_in_tag(struct usbtmc_device_data *data,
					  u8 tag)
{
	u8 *buffer;
	struct device *dev;
	int rv;
	int n;
	int actual;

	dev = &data->intf->dev;
	buffer = kmalloc(USBTMC_BUFSIZE, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_INITIATE_ABORT_BULK_IN,
			     USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_ENDPOINT,
			     tag, data->bulk_in,
			     buffer, 2, USB_CTRL_GET_TIMEOUT);

	if (rv < 0) {
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		goto exit;
	}

	dev_dbg(dev, "INITIATE_ABORT_BULK_IN returned %x with tag %02x\n",
		buffer[0], buffer[1]);

	if (buffer[0] == USBTMC_STATUS_FAILED) {
		/* No transfer in progress and the Bulk-OUT FIFO is empty. */
		rv = 0;
		goto exit;
	}

	if (buffer[0] == USBTMC_STATUS_TRANSFER_NOT_IN_PROGRESS) {
		/* The device returns this status if either:
		 * - There is a transfer in progress, but the specified bTag
		 *   does not match.
		 * - There is no transfer in progress, but the Bulk-OUT FIFO
		 *   is not empty.
		 */
		rv = -ENOMSG;
		goto exit;
	}

	if (buffer[0] != USBTMC_STATUS_SUCCESS) {
		dev_err(dev, "INITIATE_ABORT_BULK_IN returned %x\n",
			buffer[0]);
		rv = -EPERM;
		goto exit;
	}

	n = 0;

usbtmc_abort_bulk_in_status:
	dev_dbg(dev, "Reading from bulk in EP\n");

	/* Data must be present. So use low timeout 300 ms */
	actual = 0;
	rv = usb_bulk_msg(data->usb_dev,
			  usb_rcvbulkpipe(data->usb_dev,
					  data->bulk_in),
			  buffer, USBTMC_BUFSIZE,
			  &actual, 300);

	print_hex_dump_debug("usbtmc ", DUMP_PREFIX_NONE, 16, 1,
			     buffer, actual, true);

	n++;

	if (rv < 0) {
		dev_err(dev, "usb_bulk_msg returned %d\n", rv);
		if (rv != -ETIMEDOUT)
			goto exit;
	}

	if (actual == USBTMC_BUFSIZE)
		goto usbtmc_abort_bulk_in_status;

	if (n >= USBTMC_MAX_READS_TO_CLEAR_BULK_IN) {
		dev_err(dev, "Couldn't clear device buffer within %d cycles\n",
			USBTMC_MAX_READS_TO_CLEAR_BULK_IN);
		rv = -EPERM;
		goto exit;
	}

	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_CHECK_ABORT_BULK_IN_STATUS,
			     USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_ENDPOINT,
			     0, data->bulk_in, buffer, 0x08,
			     USB_CTRL_GET_TIMEOUT);

	if (rv < 0) {
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		goto exit;
	}

	dev_dbg(dev, "CHECK_ABORT_BULK_IN returned %x\n", buffer[0]);

	if (buffer[0] == USBTMC_STATUS_SUCCESS) {
		rv = 0;
		goto exit;
	}

	if (buffer[0] != USBTMC_STATUS_PENDING) {
		dev_err(dev, "CHECK_ABORT_BULK_IN returned %x\n", buffer[0]);
		rv = -EPERM;
		goto exit;
	}

	if ((buffer[1] & 1) > 0) {
		/* The device has 1 or more queued packets the Host can read */
		goto usbtmc_abort_bulk_in_status;
	}

	/* The Host must send CHECK_ABORT_BULK_IN_STATUS at a later time. */
	rv = -EAGAIN;
exit:
	kfree(buffer);
	return rv;
}