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
struct tilcdc_module {int dummy; } ;
struct tfp410_module {int /*<<< orphan*/  gpio; int /*<<< orphan*/  i2c; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct tilcdc_module* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilcdc_module_cleanup (struct tilcdc_module*) ; 
 struct tfp410_module* to_tfp410_module (struct tilcdc_module*) ; 

__attribute__((used)) static int tfp410_remove(struct platform_device *pdev)
{
	struct tilcdc_module *mod = dev_get_platdata(&pdev->dev);
	struct tfp410_module *tfp410_mod = to_tfp410_module(mod);

	i2c_put_adapter(tfp410_mod->i2c);
	gpio_free(tfp410_mod->gpio);

	tilcdc_module_cleanup(mod);

	return 0;
}