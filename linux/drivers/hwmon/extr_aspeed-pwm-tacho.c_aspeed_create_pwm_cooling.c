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
typedef  int u8 ;
typedef  int u32 ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct aspeed_pwm_tacho_data {struct aspeed_cooling_device** cdev; } ;
struct aspeed_cooling_device {int pwm_port; struct aspeed_pwm_tacho_data* priv; int /*<<< orphan*/  tcdev; int /*<<< orphan*/  name; void* cooling_levels; int /*<<< orphan*/  max_state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_CDEV_NAME_LEN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_pwm_cool_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_thermal_of_cooling_device_register (struct device*,struct device_node*,int /*<<< orphan*/ ,struct aspeed_cooling_device*,int /*<<< orphan*/ *) ; 
 int of_property_read_u8_array (struct device_node*,char*,void*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct device_node*,int) ; 

__attribute__((used)) static int aspeed_create_pwm_cooling(struct device *dev,
				     struct device_node *child,
				     struct aspeed_pwm_tacho_data *priv,
				     u32 pwm_port, u8 num_levels)
{
	int ret;
	struct aspeed_cooling_device *cdev;

	cdev = devm_kzalloc(dev, sizeof(*cdev), GFP_KERNEL);

	if (!cdev)
		return -ENOMEM;

	cdev->cooling_levels = devm_kzalloc(dev, num_levels, GFP_KERNEL);
	if (!cdev->cooling_levels)
		return -ENOMEM;

	cdev->max_state = num_levels - 1;
	ret = of_property_read_u8_array(child, "cooling-levels",
					cdev->cooling_levels,
					num_levels);
	if (ret) {
		dev_err(dev, "Property 'cooling-levels' cannot be read.\n");
		return ret;
	}
	snprintf(cdev->name, MAX_CDEV_NAME_LEN, "%pOFn%d", child, pwm_port);

	cdev->tcdev = devm_thermal_of_cooling_device_register(dev, child,
					cdev->name, cdev, &aspeed_pwm_cool_ops);
	if (IS_ERR(cdev->tcdev))
		return PTR_ERR(cdev->tcdev);

	cdev->priv = priv;
	cdev->pwm_port = pwm_port;

	priv->cdev[pwm_port] = cdev;

	return 0;
}