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
struct mlxreg_led_priv_data {int /*<<< orphan*/  access_lock; } ;

/* Variables and functions */
 struct mlxreg_led_priv_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxreg_led_remove(struct platform_device *pdev)
{
	struct mlxreg_led_priv_data *priv = dev_get_drvdata(&pdev->dev);

	mutex_destroy(&priv->access_lock);

	return 0;
}