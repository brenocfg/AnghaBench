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
struct regulator {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct i2c_board_info {char* dev_name; int irq; int /*<<< orphan*/  type; struct fwnode_handle* fwnode; } ;
struct fwnode_handle {int dummy; } ;
struct cht_int33fe_data {struct regulator* max17047; struct regulator* fusb302; struct regulator* pi3usb30532; } ;
typedef  int /*<<< orphan*/  board_info ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 unsigned long long EXPECTED_PTYPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 size_t INT33FE_NODE_FUSB302 ; 
 size_t INT33FE_NODE_PI3USB30532 ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 int acpi_dev_gpio_irq_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_dev_present (char*,char*,int) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int cht_int33fe_add_nodes (struct cht_int33fe_data*) ; 
 int cht_int33fe_register_max17047 (struct device*,struct cht_int33fe_data*) ; 
 int /*<<< orphan*/  cht_int33fe_remove_nodes (struct cht_int33fe_data*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct cht_int33fe_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* i2c_acpi_new_device (struct device*,int,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct regulator*) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nodes ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cht_int33fe_data*) ; 
 struct regulator* regulator_get_optional (struct device*,char*) ; 
 int /*<<< orphan*/  regulator_put (struct regulator*) ; 
 struct fwnode_handle* software_node_fwnode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cht_int33fe_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct i2c_board_info board_info;
	struct cht_int33fe_data *data;
	struct fwnode_handle *fwnode;
	struct regulator *regulator;
	unsigned long long ptyp;
	acpi_status status;
	int fusb302_irq;
	int ret;

	status = acpi_evaluate_integer(ACPI_HANDLE(dev), "PTYP", NULL, &ptyp);
	if (ACPI_FAILURE(status)) {
		dev_err(dev, "Error getting PTYPE\n");
		return -ENODEV;
	}

	/*
	 * The same ACPI HID is used for different configurations check PTYP
	 * to ensure that we are dealing with the expected config.
	 */
	if (ptyp != EXPECTED_PTYPE)
		return -ENODEV;

	/* Check presence of INT34D3 (hardware-rev 3) expected for ptype == 4 */
	if (!acpi_dev_present("INT34D3", "1", 3)) {
		dev_err(dev, "Error PTYPE == %d, but no INT34D3 device\n",
			EXPECTED_PTYPE);
		return -ENODEV;
	}

	/*
	 * We expect the WC PMIC to be paired with a TI bq24292i charger-IC.
	 * We check for the bq24292i vbus regulator here, this has 2 purposes:
	 * 1) The bq24292i allows charging with up to 12V, setting the fusb302's
	 *    max-snk voltage to 12V with another charger-IC is not good.
	 * 2) For the fusb302 driver to get the bq24292i vbus regulator, the
	 *    regulator-map, which is part of the bq24292i regulator_init_data,
	 *    must be registered before the fusb302 is instantiated, otherwise
	 *    it will end up with a dummy-regulator.
	 * Note "cht_wc_usb_typec_vbus" comes from the regulator_init_data
	 * which is defined in i2c-cht-wc.c from where the bq24292i i2c-client
	 * gets instantiated. We use regulator_get_optional here so that we
	 * don't end up getting a dummy-regulator ourselves.
	 */
	regulator = regulator_get_optional(dev, "cht_wc_usb_typec_vbus");
	if (IS_ERR(regulator)) {
		ret = PTR_ERR(regulator);
		return (ret == -ENODEV) ? -EPROBE_DEFER : ret;
	}
	regulator_put(regulator);

	/* The FUSB302 uses the irq at index 1 and is the only irq user */
	fusb302_irq = acpi_dev_gpio_irq_get(ACPI_COMPANION(dev), 1);
	if (fusb302_irq < 0) {
		if (fusb302_irq != -EPROBE_DEFER)
			dev_err(dev, "Error getting FUSB302 irq\n");
		return fusb302_irq;
	}

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	ret = cht_int33fe_add_nodes(data);
	if (ret)
		return ret;

	/* Work around BIOS bug, see comment on cht_int33fe_check_for_max17047 */
	ret = cht_int33fe_register_max17047(dev, data);
	if (ret)
		goto out_remove_nodes;

	fwnode = software_node_fwnode(&nodes[INT33FE_NODE_FUSB302]);
	if (!fwnode) {
		ret = -ENODEV;
		goto out_unregister_max17047;
	}

	memset(&board_info, 0, sizeof(board_info));
	strlcpy(board_info.type, "typec_fusb302", I2C_NAME_SIZE);
	board_info.dev_name = "fusb302";
	board_info.fwnode = fwnode;
	board_info.irq = fusb302_irq;

	data->fusb302 = i2c_acpi_new_device(dev, 2, &board_info);
	if (IS_ERR(data->fusb302)) {
		ret = PTR_ERR(data->fusb302);
		goto out_unregister_max17047;
	}

	fwnode = software_node_fwnode(&nodes[INT33FE_NODE_PI3USB30532]);
	if (!fwnode) {
		ret = -ENODEV;
		goto out_unregister_fusb302;
	}

	memset(&board_info, 0, sizeof(board_info));
	board_info.dev_name = "pi3usb30532";
	board_info.fwnode = fwnode;
	strlcpy(board_info.type, "pi3usb30532", I2C_NAME_SIZE);

	data->pi3usb30532 = i2c_acpi_new_device(dev, 3, &board_info);
	if (IS_ERR(data->pi3usb30532)) {
		ret = PTR_ERR(data->pi3usb30532);
		goto out_unregister_fusb302;
	}

	platform_set_drvdata(pdev, data);

	return 0;

out_unregister_fusb302:
	i2c_unregister_device(data->fusb302);

out_unregister_max17047:
	i2c_unregister_device(data->max17047);

out_remove_nodes:
	cht_int33fe_remove_nodes(data);

	return ret;
}