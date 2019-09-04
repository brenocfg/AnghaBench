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
struct mvpp2_port {int gop_id; struct mvpp2* priv; } ;
struct mvpp2 {int /*<<< orphan*/  sysctrl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENCONF_CTRL0 ; 
 int GENCONF_CTRL0_PORT0_RGMII ; 
 int GENCONF_CTRL0_PORT1_RGMII ; 
 int GENCONF_CTRL0_PORT1_RGMII_MII ; 
 int /*<<< orphan*/  GENCONF_PORT_CTRL0 ; 
 int GENCONF_PORT_CTRL0_BUS_WIDTH_SELECT ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvpp22_gop_init_rgmii(struct mvpp2_port *port)
{
	struct mvpp2 *priv = port->priv;
	u32 val;

	regmap_read(priv->sysctrl_base, GENCONF_PORT_CTRL0, &val);
	val |= GENCONF_PORT_CTRL0_BUS_WIDTH_SELECT;
	regmap_write(priv->sysctrl_base, GENCONF_PORT_CTRL0, val);

	regmap_read(priv->sysctrl_base, GENCONF_CTRL0, &val);
	if (port->gop_id == 2)
		val |= GENCONF_CTRL0_PORT0_RGMII | GENCONF_CTRL0_PORT1_RGMII;
	else if (port->gop_id == 3)
		val |= GENCONF_CTRL0_PORT1_RGMII_MII;
	regmap_write(priv->sysctrl_base, GENCONF_CTRL0, val);
}