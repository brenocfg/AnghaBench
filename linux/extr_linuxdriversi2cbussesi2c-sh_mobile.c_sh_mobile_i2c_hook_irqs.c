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
struct sh_mobile_i2c_data {int dummy; } ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sh_mobile_i2c_data*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh_mobile_i2c_isr ; 

__attribute__((used)) static int sh_mobile_i2c_hook_irqs(struct platform_device *dev, struct sh_mobile_i2c_data *pd)
{
	struct resource *res;
	resource_size_t n;
	int k = 0, ret;

	while ((res = platform_get_resource(dev, IORESOURCE_IRQ, k))) {
		for (n = res->start; n <= res->end; n++) {
			ret = devm_request_irq(&dev->dev, n, sh_mobile_i2c_isr,
					  0, dev_name(&dev->dev), pd);
			if (ret) {
				dev_err(&dev->dev, "cannot request IRQ %pa\n", &n);
				return ret;
			}
		}
		k++;
	}

	return k > 0 ? 0 : -ENOENT;
}