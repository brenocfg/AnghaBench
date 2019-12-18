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
struct cros_ec_device {int /*<<< orphan*/  dev; } ;
struct cros_ec_command {scalar_t__ result; } ;

/* Variables and functions */
 scalar_t__ EC_RES_SUCCESS ; 
 int EPROTO ; 
 int cros_ec_cmd_xfer (struct cros_ec_device*,struct cros_ec_command*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

int cros_ec_cmd_xfer_status(struct cros_ec_device *ec_dev,
			    struct cros_ec_command *msg)
{
	int ret;

	ret = cros_ec_cmd_xfer(ec_dev, msg);
	if (ret < 0) {
		dev_err(ec_dev->dev, "Command xfer error (err:%d)\n", ret);
	} else if (msg->result != EC_RES_SUCCESS) {
		dev_dbg(ec_dev->dev, "Command result (err: %d)\n", msg->result);
		return -EPROTO;
	}

	return ret;
}