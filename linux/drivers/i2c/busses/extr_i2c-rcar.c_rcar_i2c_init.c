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
struct rcar_i2c_priv {scalar_t__ devtype; int /*<<< orphan*/  icccr; } ;

/* Variables and functions */
 scalar_t__ I2C_RCAR_GEN3 ; 
 int /*<<< orphan*/  ICCCR ; 
 int /*<<< orphan*/  ICFBSCR ; 
 int /*<<< orphan*/  ICMCR ; 
 int /*<<< orphan*/  ICMIER ; 
 int /*<<< orphan*/  ICMSR ; 
 int /*<<< orphan*/  MDBS ; 
 int /*<<< orphan*/  TCYC17 ; 
 int /*<<< orphan*/  rcar_i2c_write (struct rcar_i2c_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_i2c_init(struct rcar_i2c_priv *priv)
{
	/* reset master mode */
	rcar_i2c_write(priv, ICMIER, 0);
	rcar_i2c_write(priv, ICMCR, MDBS);
	rcar_i2c_write(priv, ICMSR, 0);
	/* start clock */
	rcar_i2c_write(priv, ICCCR, priv->icccr);

	if (priv->devtype == I2C_RCAR_GEN3)
		rcar_i2c_write(priv, ICFBSCR, TCYC17);

}