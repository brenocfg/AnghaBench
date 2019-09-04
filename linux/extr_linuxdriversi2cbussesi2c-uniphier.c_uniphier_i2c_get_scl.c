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
struct uniphier_i2c_priv {scalar_t__ membase; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_I2C_BSTS ; 
 int UNIPHIER_I2C_BSTS_SCL ; 
 struct uniphier_i2c_priv* i2c_get_adapdata (struct i2c_adapter*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int uniphier_i2c_get_scl(struct i2c_adapter *adap)
{
	struct uniphier_i2c_priv *priv = i2c_get_adapdata(adap);

	return !!(readl(priv->membase + UNIPHIER_I2C_BSTS) &
							UNIPHIER_I2C_BSTS_SCL);
}