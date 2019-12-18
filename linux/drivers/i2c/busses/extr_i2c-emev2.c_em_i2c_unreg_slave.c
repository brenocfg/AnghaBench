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
struct i2c_client {int /*<<< orphan*/  adapter; } ;
struct em_i2c_device {int /*<<< orphan*/ * slave; int /*<<< orphan*/  irq; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ I2C_OFS_SVA0 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct em_i2c_device* i2c_get_adapdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int em_i2c_unreg_slave(struct i2c_client *slave)
{
	struct em_i2c_device *priv = i2c_get_adapdata(slave->adapter);

	WARN_ON(!priv->slave);

	writeb(0, priv->base + I2C_OFS_SVA0);

	/*
	 * Wait for interrupt to finish. New slave irqs cannot happen because we
	 * cleared the slave address and, thus, only extension codes will be
	 * detected which do not use the slave ptr.
	 */
	synchronize_irq(priv->irq);
	priv->slave = NULL;

	return 0;
}