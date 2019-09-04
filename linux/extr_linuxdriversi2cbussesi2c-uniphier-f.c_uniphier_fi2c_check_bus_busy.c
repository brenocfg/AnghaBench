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
struct uniphier_fi2c_priv {scalar_t__ busy_cnt; scalar_t__ membase; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ UNIPHIER_FI2C_SR ; 
 int UNIPHIER_FI2C_SR_DB ; 
 struct uniphier_fi2c_priv* i2c_get_adapdata (struct i2c_adapter*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  uniphier_fi2c_recover (struct uniphier_fi2c_priv*) ; 

__attribute__((used)) static int uniphier_fi2c_check_bus_busy(struct i2c_adapter *adap)
{
	struct uniphier_fi2c_priv *priv = i2c_get_adapdata(adap);

	if (readl(priv->membase + UNIPHIER_FI2C_SR) & UNIPHIER_FI2C_SR_DB) {
		if (priv->busy_cnt++ > 3) {
			/*
			 * If bus busy continues too long, it is probably
			 * in a wrong state.  Try bus recovery.
			 */
			uniphier_fi2c_recover(priv);
			priv->busy_cnt = 0;
		}

		return -EAGAIN;
	}

	priv->busy_cnt = 0;
	return 0;
}