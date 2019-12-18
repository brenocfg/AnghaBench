#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pm8xxx_vib {unsigned int reg_vib_drv; struct input_dev* vib_input_dev; struct pm8xxx_regs const* regs; int /*<<< orphan*/  regmap; int /*<<< orphan*/  work; } ;
struct pm8xxx_regs {unsigned int drv_en_manual_mask; int /*<<< orphan*/  drv_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_6__ {int version; } ;
struct input_dev {char* name; int /*<<< orphan*/  close; TYPE_1__ id; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct input_dev* devm_input_allocate_device (TYPE_2__*) ; 
 struct pm8xxx_vib* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int input_ff_create_memless (struct input_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct pm8xxx_vib*) ; 
 struct pm8xxx_regs* of_device_get_match_data (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pm8xxx_vib*) ; 
 int /*<<< orphan*/  pm8xxx_vib_close ; 
 int /*<<< orphan*/  pm8xxx_vib_play_effect ; 
 int /*<<< orphan*/  pm8xxx_work_handler ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pm8xxx_vib_probe(struct platform_device *pdev)
{
	struct pm8xxx_vib *vib;
	struct input_dev *input_dev;
	int error;
	unsigned int val;
	const struct pm8xxx_regs *regs;

	vib = devm_kzalloc(&pdev->dev, sizeof(*vib), GFP_KERNEL);
	if (!vib)
		return -ENOMEM;

	vib->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!vib->regmap)
		return -ENODEV;

	input_dev = devm_input_allocate_device(&pdev->dev);
	if (!input_dev)
		return -ENOMEM;

	INIT_WORK(&vib->work, pm8xxx_work_handler);
	vib->vib_input_dev = input_dev;

	regs = of_device_get_match_data(&pdev->dev);

	/* operate in manual mode */
	error = regmap_read(vib->regmap, regs->drv_addr, &val);
	if (error < 0)
		return error;

	val &= regs->drv_en_manual_mask;
	error = regmap_write(vib->regmap, regs->drv_addr, val);
	if (error < 0)
		return error;

	vib->regs = regs;
	vib->reg_vib_drv = val;

	input_dev->name = "pm8xxx_vib_ffmemless";
	input_dev->id.version = 1;
	input_dev->close = pm8xxx_vib_close;
	input_set_drvdata(input_dev, vib);
	input_set_capability(vib->vib_input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(input_dev, NULL,
					pm8xxx_vib_play_effect);
	if (error) {
		dev_err(&pdev->dev,
			"couldn't register vibrator as FF device\n");
		return error;
	}

	error = input_register_device(input_dev);
	if (error) {
		dev_err(&pdev->dev, "couldn't register input device\n");
		return error;
	}

	platform_set_drvdata(pdev, vib);
	return 0;
}