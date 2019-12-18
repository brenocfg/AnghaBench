#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  event; int /*<<< orphan*/  close; TYPE_1__ id; int /*<<< orphan*/  name; } ;
struct gpio_beeper {int /*<<< orphan*/  work; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_SND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_BELL ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct gpio_beeper* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_beeper_close ; 
 int /*<<< orphan*/  gpio_beeper_event ; 
 int /*<<< orphan*/  gpio_beeper_work ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct gpio_beeper*) ; 

__attribute__((used)) static int gpio_beeper_probe(struct platform_device *pdev)
{
	struct gpio_beeper *beep;
	struct input_dev *input;

	beep = devm_kzalloc(&pdev->dev, sizeof(*beep), GFP_KERNEL);
	if (!beep)
		return -ENOMEM;

	beep->desc = devm_gpiod_get(&pdev->dev, NULL, GPIOD_OUT_LOW);
	if (IS_ERR(beep->desc))
		return PTR_ERR(beep->desc);

	input = devm_input_allocate_device(&pdev->dev);
	if (!input)
		return -ENOMEM;

	INIT_WORK(&beep->work, gpio_beeper_work);

	input->name		= pdev->name;
	input->id.bustype	= BUS_HOST;
	input->id.vendor	= 0x0001;
	input->id.product	= 0x0001;
	input->id.version	= 0x0100;
	input->close		= gpio_beeper_close;
	input->event		= gpio_beeper_event;

	input_set_capability(input, EV_SND, SND_BELL);

	input_set_drvdata(input, beep);

	return input_register_device(input);
}