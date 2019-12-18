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
struct TYPE_4__ {int /*<<< orphan*/  ret; } ;
struct ec_response_motion_sense {TYPE_2__ kb_wake_angle; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct ec_params_motion_sense {TYPE_1__ kb_wake_angle; int /*<<< orphan*/  cmd; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cros_ec_dev {int /*<<< orphan*/  ec_dev; scalar_t__ cmd_offset; } ;
struct cros_ec_command {int version; int outsize; int insize; scalar_t__ data; scalar_t__ command; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EC_CMD_MOTION_SENSE_CMD ; 
 scalar_t__ EC_HOST_PARAM_SIZE ; 
 int /*<<< orphan*/  EC_MOTION_SENSE_NO_VALUE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_KB_WAKE_ANGLE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int cros_ec_cmd_xfer_status (int /*<<< orphan*/ ,struct cros_ec_command*) ; 
 int /*<<< orphan*/  kfree (struct cros_ec_command*) ; 
 struct cros_ec_command* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct cros_ec_dev* to_cros_ec_dev (struct device*) ; 

__attribute__((used)) static ssize_t kb_wake_angle_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct cros_ec_dev *ec = to_cros_ec_dev(dev);
	struct ec_response_motion_sense *resp;
	struct ec_params_motion_sense *param;
	struct cros_ec_command *msg;
	int ret;

	msg = kmalloc(sizeof(*msg) + EC_HOST_PARAM_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	param = (struct ec_params_motion_sense *)msg->data;
	msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;
	msg->version = 2;
	param->cmd = MOTIONSENSE_CMD_KB_WAKE_ANGLE;
	param->kb_wake_angle.data = EC_MOTION_SENSE_NO_VALUE;
	msg->outsize = sizeof(*param);
	msg->insize = sizeof(*resp);

	ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
	if (ret < 0)
		goto exit;

	resp = (struct ec_response_motion_sense *)msg->data;
	ret = scnprintf(buf, PAGE_SIZE, "%d\n", resp->kb_wake_angle.ret);
exit:
	kfree(msg);
	return ret;
}