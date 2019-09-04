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
typedef  scalar_t__ u8 ;
struct pulse8 {int* data; scalar_t__ len; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  serio; } ;

/* Variables and functions */
 int EIO ; 
 int ENOTTY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int MSGCODE_COMMAND_REJECTED ; 
 scalar_t__ const MSGCODE_GET_BUILDDATE ; 
 scalar_t__ const MSGCODE_SET_AUTO_ENABLED ; 
 scalar_t__ const MSGCODE_SET_CONTROLLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int pulse8_send (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pulse8_send_and_wait_once(struct pulse8 *pulse8,
				     const u8 *cmd, u8 cmd_len,
				     u8 response, u8 size)
{
	int err;

	/*dev_info(pulse8->dev, "transmit: %*ph\n", cmd_len, cmd);*/
	init_completion(&pulse8->cmd_done);

	err = pulse8_send(pulse8->serio, cmd, cmd_len);
	if (err)
		return err;

	if (!wait_for_completion_timeout(&pulse8->cmd_done, HZ))
		return -ETIMEDOUT;
	if ((pulse8->data[0] & 0x3f) == MSGCODE_COMMAND_REJECTED &&
	    cmd[0] != MSGCODE_SET_CONTROLLED &&
	    cmd[0] != MSGCODE_SET_AUTO_ENABLED &&
	    cmd[0] != MSGCODE_GET_BUILDDATE)
		return -ENOTTY;
	if (response &&
	    ((pulse8->data[0] & 0x3f) != response || pulse8->len < size + 1)) {
		dev_info(pulse8->dev, "transmit: failed %02x\n",
			 pulse8->data[0] & 0x3f);
		return -EIO;
	}
	return 0;
}