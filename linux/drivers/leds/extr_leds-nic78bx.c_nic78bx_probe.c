#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct nic78bx_led_data {scalar_t__ io_base; int /*<<< orphan*/  lock; struct platform_device* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  cdev; struct nic78bx_led_data* data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 scalar_t__ NIC78BX_LOCK_REG_OFFSET ; 
 int /*<<< orphan*/  NIC78BX_UNLOCK_VALUE ; 
 scalar_t__ NIC78BX_USER_LED_IO_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct nic78bx_led_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* nic78bx_leds ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct nic78bx_led_data*) ; 
 scalar_t__ resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nic78bx_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct nic78bx_led_data *led_data;
	struct resource *io_rc;
	int ret, i;

	led_data = devm_kzalloc(dev, sizeof(*led_data), GFP_KERNEL);
	if (!led_data)
		return -ENOMEM;

	led_data->pdev = pdev;
	platform_set_drvdata(pdev, led_data);

	io_rc = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!io_rc) {
		dev_err(dev, "missing IO resources\n");
		return -EINVAL;
	}

	if (resource_size(io_rc) < NIC78BX_USER_LED_IO_SIZE) {
		dev_err(dev, "IO region too small\n");
		return -EINVAL;
	}

	if (!devm_request_region(dev, io_rc->start, resource_size(io_rc),
				 KBUILD_MODNAME)) {
		dev_err(dev, "failed to get IO region\n");
		return -EBUSY;
	}

	led_data->io_base = io_rc->start;
	spin_lock_init(&led_data->lock);

	for (i = 0; i < ARRAY_SIZE(nic78bx_leds); i++) {
		nic78bx_leds[i].data = led_data;

		ret = devm_led_classdev_register(dev, &nic78bx_leds[i].cdev);
		if (ret)
			return ret;
	}

	/* Unlock LED register */
	outb(NIC78BX_UNLOCK_VALUE,
	     led_data->io_base + NIC78BX_LOCK_REG_OFFSET);

	return ret;
}