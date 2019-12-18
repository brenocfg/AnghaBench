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
struct uniphier_fi2c_priv {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_recover_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uniphier_fi2c_reset (struct uniphier_fi2c_priv*) ; 

__attribute__((used)) static void uniphier_fi2c_recover(struct uniphier_fi2c_priv *priv)
{
	uniphier_fi2c_reset(priv);
	i2c_recover_bus(&priv->adap);
}