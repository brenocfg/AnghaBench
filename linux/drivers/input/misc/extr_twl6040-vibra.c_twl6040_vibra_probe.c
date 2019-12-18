#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct vibra_info {int vibldrv_res; int vibrdrv_res; int viblmotor_res; int vibrmotor_res; scalar_t__ irq; TYPE_5__* dev; TYPE_2__* input_dev; int /*<<< orphan*/  play_work; TYPE_6__* supplies; int /*<<< orphan*/  twl6040; } ;
struct TYPE_14__ {struct device* parent; } ;
struct platform_device {TYPE_5__ dev; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_15__ {char* supply; int /*<<< orphan*/  consumer; } ;
struct TYPE_12__ {int version; } ;
struct TYPE_13__ {char* name; int /*<<< orphan*/  ffbit; int /*<<< orphan*/  close; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_6__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 TYPE_2__* devm_input_allocate_device (TYPE_5__*) ; 
 struct vibra_info* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int devm_request_threaded_irq (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vibra_info*) ; 
 int input_ff_create_memless (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct vibra_info*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vibra_info*) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  twl6040_vib_irq_handler ; 
 int /*<<< orphan*/  twl6040_vibra_close ; 
 int /*<<< orphan*/  vibra_play ; 
 int /*<<< orphan*/  vibra_play_work ; 

__attribute__((used)) static int twl6040_vibra_probe(struct platform_device *pdev)
{
	struct device *twl6040_core_dev = pdev->dev.parent;
	struct device_node *twl6040_core_node;
	struct vibra_info *info;
	int vddvibl_uV = 0;
	int vddvibr_uV = 0;
	int error;

	twl6040_core_node = of_get_child_by_name(twl6040_core_dev->of_node,
						 "vibra");
	if (!twl6040_core_node) {
		dev_err(&pdev->dev, "parent of node is missing?\n");
		return -EINVAL;
	}

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info) {
		of_node_put(twl6040_core_node);
		dev_err(&pdev->dev, "couldn't allocate memory\n");
		return -ENOMEM;
	}

	info->dev = &pdev->dev;

	info->twl6040 = dev_get_drvdata(pdev->dev.parent);

	of_property_read_u32(twl6040_core_node, "ti,vibldrv-res",
			     &info->vibldrv_res);
	of_property_read_u32(twl6040_core_node, "ti,vibrdrv-res",
			     &info->vibrdrv_res);
	of_property_read_u32(twl6040_core_node, "ti,viblmotor-res",
			     &info->viblmotor_res);
	of_property_read_u32(twl6040_core_node, "ti,vibrmotor-res",
			     &info->vibrmotor_res);
	of_property_read_u32(twl6040_core_node, "ti,vddvibl-uV", &vddvibl_uV);
	of_property_read_u32(twl6040_core_node, "ti,vddvibr-uV", &vddvibr_uV);

	of_node_put(twl6040_core_node);

	if ((!info->vibldrv_res && !info->viblmotor_res) ||
	    (!info->vibrdrv_res && !info->vibrmotor_res)) {
		dev_err(info->dev, "invalid vibra driver/motor resistance\n");
		return -EINVAL;
	}

	info->irq = platform_get_irq(pdev, 0);
	if (info->irq < 0)
		return -EINVAL;

	error = devm_request_threaded_irq(&pdev->dev, info->irq, NULL,
					  twl6040_vib_irq_handler,
					  IRQF_ONESHOT,
					  "twl6040_irq_vib", info);
	if (error) {
		dev_err(info->dev, "VIB IRQ request failed: %d\n", error);
		return error;
	}

	info->supplies[0].supply = "vddvibl";
	info->supplies[1].supply = "vddvibr";
	/*
	 * When booted with Device tree the regulators are attached to the
	 * parent device (twl6040 MFD core)
	 */
	error = devm_regulator_bulk_get(twl6040_core_dev,
					ARRAY_SIZE(info->supplies),
					info->supplies);
	if (error) {
		dev_err(info->dev, "couldn't get regulators %d\n", error);
		return error;
	}

	if (vddvibl_uV) {
		error = regulator_set_voltage(info->supplies[0].consumer,
					      vddvibl_uV, vddvibl_uV);
		if (error) {
			dev_err(info->dev, "failed to set VDDVIBL volt %d\n",
				error);
			return error;
		}
	}

	if (vddvibr_uV) {
		error = regulator_set_voltage(info->supplies[1].consumer,
					      vddvibr_uV, vddvibr_uV);
		if (error) {
			dev_err(info->dev, "failed to set VDDVIBR volt %d\n",
				error);
			return error;
		}
	}

	INIT_WORK(&info->play_work, vibra_play_work);

	info->input_dev = devm_input_allocate_device(&pdev->dev);
	if (!info->input_dev) {
		dev_err(info->dev, "couldn't allocate input device\n");
		return -ENOMEM;
	}

	input_set_drvdata(info->input_dev, info);

	info->input_dev->name = "twl6040:vibrator";
	info->input_dev->id.version = 1;
	info->input_dev->close = twl6040_vibra_close;
	__set_bit(FF_RUMBLE, info->input_dev->ffbit);

	error = input_ff_create_memless(info->input_dev, NULL, vibra_play);
	if (error) {
		dev_err(info->dev, "couldn't register vibrator to FF\n");
		return error;
	}

	error = input_register_device(info->input_dev);
	if (error) {
		dev_err(info->dev, "couldn't register input device\n");
		return error;
	}

	platform_set_drvdata(pdev, info);

	return 0;
}