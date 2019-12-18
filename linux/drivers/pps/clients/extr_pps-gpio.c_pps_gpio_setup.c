#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pps_gpio_device_data {int echo_active_ms; int assert_falling_edge; scalar_t__ echo_pin; scalar_t__ gpio_pin; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 scalar_t__ devm_gpiod_get (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct pps_gpio_device_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pps_gpio_setup(struct platform_device *pdev)
{
	struct pps_gpio_device_data *data = platform_get_drvdata(pdev);
	struct device_node *np = pdev->dev.of_node;
	int ret;
	u32 value;

	data->gpio_pin = devm_gpiod_get(&pdev->dev,
		NULL,	/* request "gpios" */
		GPIOD_IN);
	if (IS_ERR(data->gpio_pin)) {
		dev_err(&pdev->dev,
			"failed to request PPS GPIO\n");
		return PTR_ERR(data->gpio_pin);
	}

	data->echo_pin = devm_gpiod_get_optional(&pdev->dev,
			"echo",
			GPIOD_OUT_LOW);
	if (data->echo_pin) {
		if (IS_ERR(data->echo_pin)) {
			dev_err(&pdev->dev, "failed to request ECHO GPIO\n");
			return PTR_ERR(data->echo_pin);
		}

		ret = of_property_read_u32(np,
			"echo-active-ms",
			&value);
		if (ret) {
			dev_err(&pdev->dev,
				"failed to get echo-active-ms from OF\n");
			return ret;
		}
		data->echo_active_ms = value;
		/* sanity check on echo_active_ms */
		if (!data->echo_active_ms || data->echo_active_ms > 999) {
			dev_err(&pdev->dev,
				"echo-active-ms: %u - bad value from OF\n",
				data->echo_active_ms);
			return -EINVAL;
		}
	}

	if (of_property_read_bool(np, "assert-falling-edge"))
		data->assert_falling_edge = true;
	return 0;
}