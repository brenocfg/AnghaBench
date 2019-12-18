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
struct rcar_i2c_priv {int /*<<< orphan*/ * slave; int /*<<< orphan*/  irq; } ;
struct i2c_client {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICSCR ; 
 int /*<<< orphan*/  ICSIER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct rcar_i2c_priv* i2c_get_adapdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_i2c_priv_to_dev (struct rcar_i2c_priv*) ; 
 int /*<<< orphan*/  rcar_i2c_write (struct rcar_i2c_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_unreg_slave(struct i2c_client *slave)
{
	struct rcar_i2c_priv *priv = i2c_get_adapdata(slave->adapter);

	WARN_ON(!priv->slave);

	/* disable irqs and ensure none is running before clearing ptr */
	rcar_i2c_write(priv, ICSIER, 0);
	rcar_i2c_write(priv, ICSCR, 0);

	synchronize_irq(priv->irq);
	priv->slave = NULL;

	pm_runtime_put(rcar_i2c_priv_to_dev(priv));

	return 0;
}