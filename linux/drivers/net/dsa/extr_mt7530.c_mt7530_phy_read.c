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
struct mt7530_priv {int /*<<< orphan*/  bus; } ;
struct dsa_switch {struct mt7530_priv* priv; } ;

/* Variables and functions */
 int mdiobus_read_nested (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mt7530_phy_read(struct dsa_switch *ds, int port, int regnum)
{
	struct mt7530_priv *priv = ds->priv;

	return mdiobus_read_nested(priv->bus, port, regnum);
}