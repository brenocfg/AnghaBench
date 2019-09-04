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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct nsa320_hwmon {int /*<<< orphan*/  update_lock; void* data; void* clk; void* act; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct device* devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,char*,struct nsa320_hwmon*,int /*<<< orphan*/ ) ; 
 struct nsa320_hwmon* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsa320_groups ; 

__attribute__((used)) static int nsa320_hwmon_probe(struct platform_device *pdev)
{
	struct nsa320_hwmon	*hwmon;
	struct device		*classdev;

	hwmon = devm_kzalloc(&pdev->dev, sizeof(*hwmon), GFP_KERNEL);
	if (!hwmon)
		return -ENOMEM;

	/* Look up the GPIO pins to use */
	hwmon->act = devm_gpiod_get(&pdev->dev, "act", GPIOD_OUT_LOW);
	if (IS_ERR(hwmon->act))
		return PTR_ERR(hwmon->act);

	hwmon->clk = devm_gpiod_get(&pdev->dev, "clk", GPIOD_OUT_HIGH);
	if (IS_ERR(hwmon->clk))
		return PTR_ERR(hwmon->clk);

	hwmon->data = devm_gpiod_get(&pdev->dev, "data", GPIOD_IN);
	if (IS_ERR(hwmon->data))
		return PTR_ERR(hwmon->data);

	mutex_init(&hwmon->update_lock);

	classdev = devm_hwmon_device_register_with_groups(&pdev->dev,
					"nsa320", hwmon, nsa320_groups);

	return PTR_ERR_OR_ZERO(classdev);

}