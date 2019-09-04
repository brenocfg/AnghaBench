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
typedef  int u32 ;
struct TYPE_4__ {int ngpio; int /*<<< orphan*/  set_multiple; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; TYPE_3__* parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  save_regs; TYPE_1__ gc; } ;
struct xgpio_instance {int* gpio_state; int* gpio_dir; int* gpio_width; TYPE_2__ mmchip; int /*<<< orphan*/ * gpio_lock; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xgpio_instance* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int of_mm_gpiochip_add_data (struct device_node*,TYPE_2__*,struct xgpio_instance*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xgpio_instance*) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgpio_dir_in ; 
 int /*<<< orphan*/  xgpio_dir_out ; 
 int /*<<< orphan*/  xgpio_get ; 
 int /*<<< orphan*/  xgpio_save_regs ; 
 int /*<<< orphan*/  xgpio_set ; 
 int /*<<< orphan*/  xgpio_set_multiple ; 

__attribute__((used)) static int xgpio_probe(struct platform_device *pdev)
{
	struct xgpio_instance *chip;
	int status = 0;
	struct device_node *np = pdev->dev.of_node;
	u32 is_dual;

	chip = devm_kzalloc(&pdev->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	platform_set_drvdata(pdev, chip);

	/* Update GPIO state shadow register with default value */
	of_property_read_u32(np, "xlnx,dout-default", &chip->gpio_state[0]);

	/* Update GPIO direction shadow register with default value */
	if (of_property_read_u32(np, "xlnx,tri-default", &chip->gpio_dir[0]))
		chip->gpio_dir[0] = 0xFFFFFFFF;

	/*
	 * Check device node and parent device node for device width
	 * and assume default width of 32
	 */
	if (of_property_read_u32(np, "xlnx,gpio-width", &chip->gpio_width[0]))
		chip->gpio_width[0] = 32;

	spin_lock_init(&chip->gpio_lock[0]);

	if (of_property_read_u32(np, "xlnx,is-dual", &is_dual))
		is_dual = 0;

	if (is_dual) {
		/* Update GPIO state shadow register with default value */
		of_property_read_u32(np, "xlnx,dout-default-2",
				     &chip->gpio_state[1]);

		/* Update GPIO direction shadow register with default value */
		if (of_property_read_u32(np, "xlnx,tri-default-2",
					 &chip->gpio_dir[1]))
			chip->gpio_dir[1] = 0xFFFFFFFF;

		/*
		 * Check device node and parent device node for device width
		 * and assume default width of 32
		 */
		if (of_property_read_u32(np, "xlnx,gpio2-width",
					 &chip->gpio_width[1]))
			chip->gpio_width[1] = 32;

		spin_lock_init(&chip->gpio_lock[1]);
	}

	chip->mmchip.gc.ngpio = chip->gpio_width[0] + chip->gpio_width[1];
	chip->mmchip.gc.parent = &pdev->dev;
	chip->mmchip.gc.direction_input = xgpio_dir_in;
	chip->mmchip.gc.direction_output = xgpio_dir_out;
	chip->mmchip.gc.get = xgpio_get;
	chip->mmchip.gc.set = xgpio_set;
	chip->mmchip.gc.set_multiple = xgpio_set_multiple;

	chip->mmchip.save_regs = xgpio_save_regs;

	/* Call the OF gpio helper to setup and register the GPIO device */
	status = of_mm_gpiochip_add_data(np, &chip->mmchip, chip);
	if (status) {
		pr_err("%pOF: error in probe function with status %d\n",
		       np, status);
		return status;
	}

	return 0;
}