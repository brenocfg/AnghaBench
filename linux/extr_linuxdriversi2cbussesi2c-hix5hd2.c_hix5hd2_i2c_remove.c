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
struct platform_device {int dummy; } ;
struct hix5hd2_i2c_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct hix5hd2_i2c_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hix5hd2_i2c_remove(struct platform_device *pdev)
{
	struct hix5hd2_i2c_priv *priv = platform_get_drvdata(pdev);

	i2c_del_adapter(&priv->adap);
	pm_runtime_disable(priv->dev);
	pm_runtime_set_suspended(priv->dev);

	return 0;
}