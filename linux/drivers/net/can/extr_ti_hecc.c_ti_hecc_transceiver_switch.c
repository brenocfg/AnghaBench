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
struct ti_hecc_priv {int /*<<< orphan*/  reg_xceiver; } ;

/* Variables and functions */
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_hecc_transceiver_switch(const struct ti_hecc_priv *priv,
				      int on)
{
	if (!priv->reg_xceiver)
		return 0;

	if (on)
		return regulator_enable(priv->reg_xceiver);
	else
		return regulator_disable(priv->reg_xceiver);
}