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
typedef  int u32 ;
struct nb8800_priv {int dummy; } ;
struct mii_bus {struct nb8800_priv* priv; } ;

/* Variables and functions */
 int MDIO_CMD_GO ; 
 int /*<<< orphan*/  NB8800_MDIO_CMD ; 
 int nb8800_mdio_wait (struct mii_bus*) ; 
 int /*<<< orphan*/  nb8800_writel (struct nb8800_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int nb8800_mdio_cmd(struct mii_bus *bus, u32 cmd)
{
	struct nb8800_priv *priv = bus->priv;
	int err;

	err = nb8800_mdio_wait(bus);
	if (err)
		return err;

	nb8800_writel(priv, NB8800_MDIO_CMD, cmd);
	udelay(10);
	nb8800_writel(priv, NB8800_MDIO_CMD, cmd | MDIO_CMD_GO);

	return nb8800_mdio_wait(bus);
}