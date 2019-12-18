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
struct mlxcpld_i2c_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct mlxcpld_i2c_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mlxcpld_i2c_remove(struct platform_device *pdev)
{
	struct mlxcpld_i2c_priv *priv = platform_get_drvdata(pdev);

	i2c_del_adapter(&priv->adap);
	mutex_destroy(&priv->lock);

	return 0;
}