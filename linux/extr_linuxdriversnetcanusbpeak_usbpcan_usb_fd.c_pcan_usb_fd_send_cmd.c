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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct peak_usb_device {int state; int /*<<< orphan*/  netdev; TYPE_1__* udev; } ;
typedef  int ptrdiff_t ;
struct TYPE_3__ {scalar_t__ speed; } ;

/* Variables and functions */
 int PCAN_UFD_CMD_BUFFER_SIZE ; 
 int /*<<< orphan*/  PCAN_UFD_CMD_TIMEOUT_MS ; 
 int PCAN_UFD_LOSPD_PKT_SIZE ; 
 int /*<<< orphan*/  PCAN_USBPRO_EP_CMDOUT ; 
 int PCAN_USB_STATE_CONNECTED ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* pcan_usb_fd_cmd_buffer (struct peak_usb_device*) ; 
 scalar_t__ unlikely (int) ; 
 int usb_bulk_msg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_fd_send_cmd(struct peak_usb_device *dev, void *cmd_tail)
{
	void *cmd_head = pcan_usb_fd_cmd_buffer(dev);
	int err = 0;
	u8 *packet_ptr;
	int packet_len;
	ptrdiff_t cmd_len;

	/* usb device unregistered? */
	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		return 0;

	/* if a packet is not filled completely by commands, the command list
	 * is terminated with an "end of collection" record.
	 */
	cmd_len = cmd_tail - cmd_head;
	if (cmd_len <= (PCAN_UFD_CMD_BUFFER_SIZE - sizeof(u64))) {
		memset(cmd_tail, 0xff, sizeof(u64));
		cmd_len += sizeof(u64);
	}

	packet_ptr = cmd_head;
	packet_len = cmd_len;

	/* firmware is not able to re-assemble 512 bytes buffer in full-speed */
	if (unlikely(dev->udev->speed != USB_SPEED_HIGH))
		packet_len = min(packet_len, PCAN_UFD_LOSPD_PKT_SIZE);

	do {
		err = usb_bulk_msg(dev->udev,
				   usb_sndbulkpipe(dev->udev,
						   PCAN_USBPRO_EP_CMDOUT),
				   packet_ptr, packet_len,
				   NULL, PCAN_UFD_CMD_TIMEOUT_MS);
		if (err) {
			netdev_err(dev->netdev,
				   "sending command failure: %d\n", err);
			break;
		}

		packet_ptr += packet_len;
		cmd_len -= packet_len;

		if (cmd_len < PCAN_UFD_LOSPD_PKT_SIZE)
			packet_len = cmd_len;

	} while (packet_len > 0);

	return err;
}