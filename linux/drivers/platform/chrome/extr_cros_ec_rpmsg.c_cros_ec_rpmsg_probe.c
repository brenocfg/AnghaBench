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
struct device {int dummy; } ;
struct rpmsg_device {struct device dev; } ;
struct ec_response_get_protocol_info {int dummy; } ;
struct ec_host_response {int dummy; } ;
struct ec_host_request {int dummy; } ;
struct cros_ec_rpmsg {int /*<<< orphan*/  host_event_work; int /*<<< orphan*/  ept; int /*<<< orphan*/  xfer_ack; struct rpmsg_device* rpdev; } ;
struct cros_ec_device {int din_size; int dout_size; int /*<<< orphan*/  phys_name; int /*<<< orphan*/  pkt_xfer; int /*<<< orphan*/  cmd_xfer; struct cros_ec_rpmsg* priv; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cros_ec_cmd_xfer_rpmsg ; 
 int /*<<< orphan*/  cros_ec_pkt_xfer_rpmsg ; 
 int cros_ec_register (struct cros_ec_device*) ; 
 int /*<<< orphan*/  cros_ec_rpmsg_create_ept (struct rpmsg_device*) ; 
 int /*<<< orphan*/  cros_ec_rpmsg_host_event_function ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct cros_ec_device*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpmsg_destroy_ept (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cros_ec_rpmsg_probe(struct rpmsg_device *rpdev)
{
	struct device *dev = &rpdev->dev;
	struct cros_ec_rpmsg *ec_rpmsg;
	struct cros_ec_device *ec_dev;
	int ret;

	ec_dev = devm_kzalloc(dev, sizeof(*ec_dev), GFP_KERNEL);
	if (!ec_dev)
		return -ENOMEM;

	ec_rpmsg = devm_kzalloc(dev, sizeof(*ec_rpmsg), GFP_KERNEL);
	if (!ec_rpmsg)
		return -ENOMEM;

	ec_dev->dev = dev;
	ec_dev->priv = ec_rpmsg;
	ec_dev->cmd_xfer = cros_ec_cmd_xfer_rpmsg;
	ec_dev->pkt_xfer = cros_ec_pkt_xfer_rpmsg;
	ec_dev->phys_name = dev_name(&rpdev->dev);
	ec_dev->din_size = sizeof(struct ec_host_response) +
			   sizeof(struct ec_response_get_protocol_info);
	ec_dev->dout_size = sizeof(struct ec_host_request);
	dev_set_drvdata(dev, ec_dev);

	ec_rpmsg->rpdev = rpdev;
	init_completion(&ec_rpmsg->xfer_ack);
	INIT_WORK(&ec_rpmsg->host_event_work,
		  cros_ec_rpmsg_host_event_function);

	ec_rpmsg->ept = cros_ec_rpmsg_create_ept(rpdev);
	if (!ec_rpmsg->ept)
		return -ENOMEM;

	ret = cros_ec_register(ec_dev);
	if (ret < 0) {
		rpmsg_destroy_ept(ec_rpmsg->ept);
		cancel_work_sync(&ec_rpmsg->host_event_work);
		return ret;
	}

	return 0;
}