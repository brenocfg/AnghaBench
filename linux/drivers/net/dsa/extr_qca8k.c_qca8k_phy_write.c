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
typedef  int /*<<< orphan*/  u16 ;
struct qca8k_priv {int dummy; } ;
struct dsa_switch {struct qca8k_priv* priv; } ;

/* Variables and functions */
 int qca8k_mdio_write (struct qca8k_priv*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qca8k_phy_write(struct dsa_switch *ds, int port, int regnum, u16 data)
{
	struct qca8k_priv *priv = ds->priv;

	return qca8k_mdio_write(priv, port, regnum, data);
}