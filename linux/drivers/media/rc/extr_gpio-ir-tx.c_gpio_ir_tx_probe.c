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
struct rc_dev {int /*<<< orphan*/  s_tx_carrier; int /*<<< orphan*/  s_tx_duty_cycle; int /*<<< orphan*/  tx_ir; int /*<<< orphan*/  device_name; int /*<<< orphan*/  driver_name; struct gpio_ir* priv; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gpio_ir {int carrier; int duty_cycle; int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW_TX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct gpio_ir* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct rc_dev* devm_rc_allocate_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_rc_register_device (int /*<<< orphan*/ *,struct rc_dev*) ; 
 int /*<<< orphan*/  gpio_ir_tx ; 
 int /*<<< orphan*/  gpio_ir_tx_set_carrier ; 
 int /*<<< orphan*/  gpio_ir_tx_set_duty_cycle ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpio_ir_tx_probe(struct platform_device *pdev)
{
	struct gpio_ir *gpio_ir;
	struct rc_dev *rcdev;
	int rc;

	gpio_ir = devm_kmalloc(&pdev->dev, sizeof(*gpio_ir), GFP_KERNEL);
	if (!gpio_ir)
		return -ENOMEM;

	rcdev = devm_rc_allocate_device(&pdev->dev, RC_DRIVER_IR_RAW_TX);
	if (!rcdev)
		return -ENOMEM;

	gpio_ir->gpio = devm_gpiod_get(&pdev->dev, NULL, GPIOD_OUT_LOW);
	if (IS_ERR(gpio_ir->gpio)) {
		if (PTR_ERR(gpio_ir->gpio) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get gpio (%ld)\n",
				PTR_ERR(gpio_ir->gpio));
		return PTR_ERR(gpio_ir->gpio);
	}

	rcdev->priv = gpio_ir;
	rcdev->driver_name = DRIVER_NAME;
	rcdev->device_name = DEVICE_NAME;
	rcdev->tx_ir = gpio_ir_tx;
	rcdev->s_tx_duty_cycle = gpio_ir_tx_set_duty_cycle;
	rcdev->s_tx_carrier = gpio_ir_tx_set_carrier;

	gpio_ir->carrier = 38000;
	gpio_ir->duty_cycle = 50;
	spin_lock_init(&gpio_ir->lock);

	rc = devm_rc_register_device(&pdev->dev, rcdev);
	if (rc < 0)
		dev_err(&pdev->dev, "failed to register rc device\n");

	return rc;
}