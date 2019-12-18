#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvaser_usb {TYPE_1__* intf; TYPE_2__* bulk_in; } ;
struct kvaser_cmd {int len; } ;
struct TYPE_4__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CMD_HEADER_LEN ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_handle_command (struct kvaser_usb*,struct kvaser_cmd*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int round_up (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvaser_usb_leaf_read_bulk_callback(struct kvaser_usb *dev,
					       void *buf, int len)
{
	struct kvaser_cmd *cmd;
	int pos = 0;

	while (pos <= len - CMD_HEADER_LEN) {
		cmd = buf + pos;

		/* The Kvaser firmware can only read and write commands that
		 * does not cross the USB's endpoint wMaxPacketSize boundary.
		 * If a follow-up command crosses such boundary, firmware puts
		 * a placeholder zero-length command in its place then aligns
		 * the real command to the next max packet size.
		 *
		 * Handle such cases or we're going to miss a significant
		 * number of events in case of a heavy rx load on the bus.
		 */
		if (cmd->len == 0) {
			pos = round_up(pos, le16_to_cpu
						(dev->bulk_in->wMaxPacketSize));
			continue;
		}

		if (pos + cmd->len > len) {
			dev_err_ratelimited(&dev->intf->dev, "Format error\n");
			break;
		}

		kvaser_usb_leaf_handle_command(dev, cmd);
		pos += cmd->len;
	}
}