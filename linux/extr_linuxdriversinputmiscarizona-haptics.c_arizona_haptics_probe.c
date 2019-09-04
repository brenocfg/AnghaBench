#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_5__ dev; } ;
struct arizona_haptics {TYPE_2__* input_dev; int /*<<< orphan*/  work; struct arizona* arizona; } ;
struct TYPE_8__ {int /*<<< orphan*/  hap_act; } ;
struct arizona {int /*<<< orphan*/  dev; TYPE_1__ pdata; int /*<<< orphan*/  regmap; } ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  ffbit; int /*<<< orphan*/  close; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_HAPTICS_CONTROL_1 ; 
 int /*<<< orphan*/  ARIZONA_HAP_ACT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arizona_haptics_close ; 
 int /*<<< orphan*/  arizona_haptics_play ; 
 int /*<<< orphan*/  arizona_haptics_work ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_input_allocate_device (TYPE_5__*) ; 
 struct arizona_haptics* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int input_ff_create_memless (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct arizona_haptics*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arizona_haptics_probe(struct platform_device *pdev)
{
	struct arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	struct arizona_haptics *haptics;
	int ret;

	haptics = devm_kzalloc(&pdev->dev, sizeof(*haptics), GFP_KERNEL);
	if (!haptics)
		return -ENOMEM;

	haptics->arizona = arizona;

	ret = regmap_update_bits(arizona->regmap, ARIZONA_HAPTICS_CONTROL_1,
				 ARIZONA_HAP_ACT, arizona->pdata.hap_act);
	if (ret != 0) {
		dev_err(arizona->dev, "Failed to set haptics actuator: %d\n",
			ret);
		return ret;
	}

	INIT_WORK(&haptics->work, arizona_haptics_work);

	haptics->input_dev = devm_input_allocate_device(&pdev->dev);
	if (!haptics->input_dev) {
		dev_err(arizona->dev, "Failed to allocate input device\n");
		return -ENOMEM;
	}

	input_set_drvdata(haptics->input_dev, haptics);

	haptics->input_dev->name = "arizona:haptics";
	haptics->input_dev->close = arizona_haptics_close;
	__set_bit(FF_RUMBLE, haptics->input_dev->ffbit);

	ret = input_ff_create_memless(haptics->input_dev, NULL,
				      arizona_haptics_play);
	if (ret < 0) {
		dev_err(arizona->dev, "input_ff_create_memless() failed: %d\n",
			ret);
		return ret;
	}

	ret = input_register_device(haptics->input_dev);
	if (ret < 0) {
		dev_err(arizona->dev, "couldn't register input device: %d\n",
			ret);
		return ret;
	}

	return 0;
}