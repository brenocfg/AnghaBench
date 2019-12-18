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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  event_type; } ;
struct cros_ec_device {int event_size; TYPE_1__ event_data; } ;
struct cros_ec_command {int insize; int /*<<< orphan*/  data; scalar_t__ outsize; int /*<<< orphan*/  command; scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_MKBP_STATE ; 
 int /*<<< orphan*/  EC_MKBP_EVENT_KEY_MATRIX ; 
 int cros_ec_cmd_xfer (struct cros_ec_device*,struct cros_ec_command*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_keyboard_state_event(struct cros_ec_device *ec_dev)
{
	u8 buffer[sizeof(struct cros_ec_command) +
		  sizeof(ec_dev->event_data.data)];
	struct cros_ec_command *msg = (struct cros_ec_command *)&buffer;

	msg->version = 0;
	msg->command = EC_CMD_MKBP_STATE;
	msg->insize = sizeof(ec_dev->event_data.data);
	msg->outsize = 0;

	ec_dev->event_size = cros_ec_cmd_xfer(ec_dev, msg);
	ec_dev->event_data.event_type = EC_MKBP_EVENT_KEY_MATRIX;
	memcpy(&ec_dev->event_data.data, msg->data,
	       sizeof(ec_dev->event_data.data));

	return ec_dev->event_size;
}