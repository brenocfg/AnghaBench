#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {struct cpcap_charger_ddata* drv_data; int /*<<< orphan*/  of_node; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  set_vbus; } ;
struct cpcap_charger_ddata {int /*<<< orphan*/  detect_work; TYPE_2__* dev; TYPE_1__ comparator; int /*<<< orphan*/  usb; int /*<<< orphan*/  active; int /*<<< orphan*/  vbus_work; int /*<<< orphan*/  irq_list; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpcap_charger_id_table ; 
 int cpcap_charger_init_iio (struct cpcap_charger_ddata*) ; 
 int /*<<< orphan*/  cpcap_charger_init_optional_gpios (struct cpcap_charger_ddata*) ; 
 int /*<<< orphan*/  cpcap_charger_set_vbus ; 
 int /*<<< orphan*/  cpcap_charger_usb_desc ; 
 int /*<<< orphan*/  cpcap_charger_vbus_work ; 
 int /*<<< orphan*/  cpcap_usb_detect ; 
 int cpcap_usb_init_interrupts (struct platform_device*,struct cpcap_charger_ddata*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 struct cpcap_charger_ddata* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (TYPE_2__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int omap_usb2_set_comparator (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cpcap_charger_ddata*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpcap_charger_probe(struct platform_device *pdev)
{
	struct cpcap_charger_ddata *ddata;
	const struct of_device_id *of_id;
	struct power_supply_config psy_cfg = {};
	int error;

	of_id = of_match_device(of_match_ptr(cpcap_charger_id_table),
				&pdev->dev);
	if (!of_id)
		return -EINVAL;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	ddata->dev = &pdev->dev;

	ddata->reg = dev_get_regmap(ddata->dev->parent, NULL);
	if (!ddata->reg)
		return -ENODEV;

	INIT_LIST_HEAD(&ddata->irq_list);
	INIT_DELAYED_WORK(&ddata->detect_work, cpcap_usb_detect);
	INIT_DELAYED_WORK(&ddata->vbus_work, cpcap_charger_vbus_work);
	platform_set_drvdata(pdev, ddata);

	error = cpcap_charger_init_iio(ddata);
	if (error)
		return error;

	atomic_set(&ddata->active, 1);

	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.drv_data = ddata;

	ddata->usb = devm_power_supply_register(ddata->dev,
						&cpcap_charger_usb_desc,
						&psy_cfg);
	if (IS_ERR(ddata->usb)) {
		error = PTR_ERR(ddata->usb);
		dev_err(ddata->dev, "failed to register USB charger: %i\n",
			error);

		return error;
	}

	error = cpcap_usb_init_interrupts(pdev, ddata);
	if (error)
		return error;

	ddata->comparator.set_vbus = cpcap_charger_set_vbus;
	error = omap_usb2_set_comparator(&ddata->comparator);
	if (error == -ENODEV) {
		dev_info(ddata->dev, "charger needs phy, deferring probe\n");
		return -EPROBE_DEFER;
	}

	cpcap_charger_init_optional_gpios(ddata);

	schedule_delayed_work(&ddata->detect_work, 0);

	return 0;
}