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
struct TYPE_4__ {TYPE_1__* fwnode; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct i2c_board_info {char* dev_name; struct fwnode_handle* fwnode; int /*<<< orphan*/  type; } ;
struct fwnode_handle {int /*<<< orphan*/  secondary; } ;
struct device {int dummy; } ;
struct cht_int33fe_data {int /*<<< orphan*/  max17047; } ;
typedef  int /*<<< orphan*/  board_info ;
struct TYPE_3__ {struct fwnode_handle* secondary; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ERR_PTR (int) ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 size_t INT33FE_NODE_MAX17047 ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cht_int33fe_check_for_max17047 ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int device_reprobe (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_acpi_new_device (struct device*,int,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_for_each_dev (struct i2c_client**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nodes ; 
 struct fwnode_handle* software_node_fwnode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cht_int33fe_register_max17047(struct device *dev, struct cht_int33fe_data *data)
{
	struct i2c_client *max17047 = NULL;
	struct i2c_board_info board_info;
	struct fwnode_handle *fwnode;
	int ret;

	fwnode = software_node_fwnode(&nodes[INT33FE_NODE_MAX17047]);
	if (!fwnode)
		return -ENODEV;

	i2c_for_each_dev(&max17047, cht_int33fe_check_for_max17047);
	if (max17047) {
		/* Pre-existing i2c-client for the max17047, add device-props */
		fwnode->secondary = ERR_PTR(-ENODEV);
		max17047->dev.fwnode->secondary = fwnode;
		/* And re-probe to get the new device-props applied. */
		ret = device_reprobe(&max17047->dev);
		if (ret)
			dev_warn(dev, "Reprobing max17047 error: %d\n", ret);
		return 0;
	}

	memset(&board_info, 0, sizeof(board_info));
	strlcpy(board_info.type, "max17047", I2C_NAME_SIZE);
	board_info.dev_name = "max17047";
	board_info.fwnode = fwnode;
	data->max17047 = i2c_acpi_new_device(dev, 1, &board_info);

	return PTR_ERR_OR_ZERO(data->max17047);
}