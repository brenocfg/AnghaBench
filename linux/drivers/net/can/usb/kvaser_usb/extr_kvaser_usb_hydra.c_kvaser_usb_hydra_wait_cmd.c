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
typedef  scalar_t__ u8 ;
struct kvaser_usb {TYPE_1__* intf; } ;
struct TYPE_4__ {scalar_t__ cmd_no; } ;
struct kvaser_cmd {TYPE_2__ header; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CMD_EXTENDED ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KVASER_USB_RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  KVASER_USB_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree (void*) ; 
 size_t kvaser_usb_hydra_cmd_size (struct kvaser_cmd*) ; 
 int kvaser_usb_recv_cmd (struct kvaser_usb const*,void*,int /*<<< orphan*/ ,int*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct kvaser_cmd*,struct kvaser_cmd*,size_t) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int kvaser_usb_hydra_wait_cmd(const struct kvaser_usb *dev, u8 cmd_no,
				     struct kvaser_cmd *cmd)
{
	void *buf;
	int err;
	unsigned long timeout = jiffies + msecs_to_jiffies(KVASER_USB_TIMEOUT);

	if (cmd->header.cmd_no == CMD_EXTENDED) {
		dev_err(&dev->intf->dev, "Wait for CMD_EXTENDED not allowed\n");
		return -EINVAL;
	}

	buf = kzalloc(KVASER_USB_RX_BUFFER_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	do {
		int actual_len = 0;
		int pos = 0;

		err = kvaser_usb_recv_cmd(dev, buf, KVASER_USB_RX_BUFFER_SIZE,
					  &actual_len);
		if (err < 0)
			goto end;

		while (pos < actual_len) {
			struct kvaser_cmd *tmp_cmd;
			size_t cmd_len;

			tmp_cmd = buf + pos;
			cmd_len = kvaser_usb_hydra_cmd_size(tmp_cmd);
			if (pos + cmd_len > actual_len) {
				dev_err_ratelimited(&dev->intf->dev,
						    "Format error\n");
				break;
			}

			if (tmp_cmd->header.cmd_no == cmd_no) {
				memcpy(cmd, tmp_cmd, cmd_len);
				goto end;
			}
			pos += cmd_len;
		}
	} while (time_before(jiffies, timeout));

	err = -EINVAL;

end:
	kfree(buf);

	return err;
}