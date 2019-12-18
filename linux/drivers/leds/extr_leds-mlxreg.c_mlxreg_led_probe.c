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
struct mlxreg_led_priv_data {struct mlxreg_core_platform_data* pdata; struct platform_device* pdev; int /*<<< orphan*/  access_lock; } ;
struct mlxreg_core_platform_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct mlxreg_core_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct mlxreg_led_priv_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mlxreg_led_config (struct mlxreg_led_priv_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxreg_led_probe(struct platform_device *pdev)
{
	struct mlxreg_core_platform_data *led_pdata;
	struct mlxreg_led_priv_data *priv;

	led_pdata = dev_get_platdata(&pdev->dev);
	if (!led_pdata) {
		dev_err(&pdev->dev, "Failed to get platform data.\n");
		return -EINVAL;
	}

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_init(&priv->access_lock);
	priv->pdev = pdev;
	priv->pdata = led_pdata;

	return mlxreg_led_config(priv);
}