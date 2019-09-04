#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct vibra_info {int enabled; TYPE_2__* input_dev; int /*<<< orphan*/  play_work; int /*<<< orphan*/  base; int /*<<< orphan*/  regmap; } ;
struct TYPE_13__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_6__ dev; } ;
struct TYPE_11__ {scalar_t__ version; } ;
struct TYPE_12__ {char* name; int /*<<< orphan*/  close; TYPE_1__ id; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int device_property_read_u32 (TYPE_6__*,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* devm_input_allocate_device (TYPE_6__*) ; 
 struct vibra_info* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int input_ff_create_memless (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct vibra_info*) ; 
 int /*<<< orphan*/  sc27xx_vibra_close ; 
 int sc27xx_vibra_hw_init (struct vibra_info*) ; 
 int /*<<< orphan*/  sc27xx_vibra_play ; 
 int /*<<< orphan*/  sc27xx_vibra_play_work ; 

__attribute__((used)) static int sc27xx_vibra_probe(struct platform_device *pdev)
{
	struct vibra_info *info;
	int error;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!info->regmap) {
		dev_err(&pdev->dev, "failed to get vibrator regmap.\n");
		return -ENODEV;
	}

	error = device_property_read_u32(&pdev->dev, "reg", &info->base);
	if (error) {
		dev_err(&pdev->dev, "failed to get vibrator base address.\n");
		return error;
	}

	info->input_dev = devm_input_allocate_device(&pdev->dev);
	if (!info->input_dev) {
		dev_err(&pdev->dev, "failed to allocate input device.\n");
		return -ENOMEM;
	}

	info->input_dev->name = "sc27xx:vibrator";
	info->input_dev->id.version = 0;
	info->input_dev->close = sc27xx_vibra_close;

	input_set_drvdata(info->input_dev, info);
	input_set_capability(info->input_dev, EV_FF, FF_RUMBLE);
	INIT_WORK(&info->play_work, sc27xx_vibra_play_work);
	info->enabled = false;

	error = sc27xx_vibra_hw_init(info);
	if (error) {
		dev_err(&pdev->dev, "failed to initialize the vibrator.\n");
		return error;
	}

	error = input_ff_create_memless(info->input_dev, NULL,
					sc27xx_vibra_play);
	if (error) {
		dev_err(&pdev->dev, "failed to register vibrator to FF.\n");
		return error;
	}

	error = input_register_device(info->input_dev);
	if (error) {
		dev_err(&pdev->dev, "failed to register input device.\n");
		return error;
	}

	return 0;
}