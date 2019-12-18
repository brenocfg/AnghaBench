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
struct ishtp_cl_data {int /*<<< orphan*/  cros_ish_cl; struct cros_ec_device* ec_dev; } ;
struct ec_response_get_protocol_info {int dummy; } ;
struct device {struct cros_ec_device* driver_data; } ;
struct cros_ish_out_msg {int dummy; } ;
struct cros_ish_in_msg {int dummy; } ;
struct cros_ec_device {int din_size; int dout_size; int /*<<< orphan*/  phys_name; int /*<<< orphan*/  pkt_xfer; int /*<<< orphan*/ * cmd_xfer; int /*<<< orphan*/  priv; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct device* cl_data_to_dev (struct ishtp_cl_data*) ; 
 int /*<<< orphan*/  cros_ec_pkt_xfer_ish ; 
 int cros_ec_register (struct cros_ec_device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct cros_ec_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cros_ec_dev_init(struct ishtp_cl_data *client_data)
{
	struct cros_ec_device *ec_dev;
	struct device *dev = cl_data_to_dev(client_data);

	ec_dev = devm_kzalloc(dev, sizeof(*ec_dev), GFP_KERNEL);
	if (!ec_dev)
		return -ENOMEM;

	client_data->ec_dev = ec_dev;
	dev->driver_data = ec_dev;

	ec_dev->dev = dev;
	ec_dev->priv = client_data->cros_ish_cl;
	ec_dev->cmd_xfer = NULL;
	ec_dev->pkt_xfer = cros_ec_pkt_xfer_ish;
	ec_dev->phys_name = dev_name(dev);
	ec_dev->din_size = sizeof(struct cros_ish_in_msg) +
			   sizeof(struct ec_response_get_protocol_info);
	ec_dev->dout_size = sizeof(struct cros_ish_out_msg);

	return cros_ec_register(ec_dev);
}