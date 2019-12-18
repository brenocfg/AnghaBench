#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  netfn; } ;
struct TYPE_4__ {scalar_t__* data; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct ibmpex_bmc_data {int interface; int /*<<< orphan*/  user; int /*<<< orphan*/  hwmon_dev; struct device* bmc_device; int /*<<< orphan*/  list; int /*<<< orphan*/  tx_msg_data; TYPE_2__ tx_message; int /*<<< orphan*/  read_complete; scalar_t__ tx_msgid; int /*<<< orphan*/  lock; TYPE_1__ address; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bmc_data; int /*<<< orphan*/  ipmi_hndlrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PEX_COMMAND ; 
 int /*<<< orphan*/  PEX_NET_FUNCTION ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ibmpex_bmc_data*) ; 
 TYPE_3__ driver_data ; 
 int /*<<< orphan*/  hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int ibmpex_find_sensors (struct ibmpex_bmc_data*) ; 
 int ibmpex_ver_check (struct ibmpex_bmc_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int ipmi_create_user (int,int /*<<< orphan*/ *,struct ibmpex_bmc_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ibmpex_bmc_data*) ; 
 struct ibmpex_bmc_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmpex_register_bmc(int iface, struct device *dev)
{
	struct ibmpex_bmc_data *data;
	int err;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return;

	data->address.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	data->address.channel = IPMI_BMC_CHANNEL;
	data->address.data[0] = 0;
	data->interface = iface;
	data->bmc_device = dev;

	/* Create IPMI messaging interface user */
	err = ipmi_create_user(data->interface, &driver_data.ipmi_hndlrs,
			       data, &data->user);
	if (err < 0) {
		dev_err(dev,
			"Unable to register user with IPMI interface %d\n",
			data->interface);
		goto out;
	}

	mutex_init(&data->lock);

	/* Initialize message */
	data->tx_msgid = 0;
	init_completion(&data->read_complete);
	data->tx_message.netfn = PEX_NET_FUNCTION;
	data->tx_message.cmd = PEX_COMMAND;
	data->tx_message.data = data->tx_msg_data;

	/* Does this BMC support PowerExecutive? */
	err = ibmpex_ver_check(data);
	if (err)
		goto out_user;

	/* Register the BMC as a HWMON class device */
	data->hwmon_dev = hwmon_device_register(data->bmc_device);

	if (IS_ERR(data->hwmon_dev)) {
		dev_err(data->bmc_device,
			"Unable to register hwmon device for IPMI interface %d\n",
			data->interface);
		goto out_user;
	}

	/* finally add the new bmc data to the bmc data list */
	dev_set_drvdata(dev, data);
	list_add_tail(&data->list, &driver_data.bmc_data);

	/* Now go find all the sensors */
	err = ibmpex_find_sensors(data);
	if (err) {
		dev_err(data->bmc_device, "Error %d finding sensors\n", err);
		goto out_register;
	}

	return;

out_register:
	hwmon_device_unregister(data->hwmon_dev);
out_user:
	ipmi_destroy_user(data->user);
out:
	kfree(data);
}