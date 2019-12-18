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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  enable; } ;
struct ec_params_lightbar {TYPE_1__ manual_suspend_ctrl; int /*<<< orphan*/  cmd; } ;
struct cros_ec_dev {int /*<<< orphan*/  ec_dev; } ;
struct cros_ec_command {scalar_t__ result; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ EC_RES_SUCCESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIGHTBAR_CMD_MANUAL_SUSPEND_CTRL ; 
 struct cros_ec_command* alloc_lightbar_cmd_msg (struct cros_ec_dev*) ; 
 int cros_ec_cmd_xfer (int /*<<< orphan*/ ,struct cros_ec_command*) ; 
 int /*<<< orphan*/  kfree (struct cros_ec_command*) ; 
 int lb_throttle () ; 

__attribute__((used)) static int lb_manual_suspend_ctrl(struct cros_ec_dev *ec, uint8_t enable)
{
	struct ec_params_lightbar *param;
	struct cros_ec_command *msg;
	int ret;

	msg = alloc_lightbar_cmd_msg(ec);
	if (!msg)
		return -ENOMEM;

	param = (struct ec_params_lightbar *)msg->data;

	param->cmd = LIGHTBAR_CMD_MANUAL_SUSPEND_CTRL;
	param->manual_suspend_ctrl.enable = enable;

	ret = lb_throttle();
	if (ret)
		goto error;

	ret = cros_ec_cmd_xfer(ec->ec_dev, msg);
	if (ret < 0)
		goto error;
	if (msg->result != EC_RES_SUCCESS) {
		ret = -EINVAL;
		goto error;
	}
	ret = 0;
error:
	kfree(msg);

	return ret;
}