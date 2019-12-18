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
struct ocelot_port {int /*<<< orphan*/  chip_port; struct ocelot* ocelot; } ;
struct ocelot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_PORT_CPU_FWD_CFG ; 
 int ANA_PORT_CPU_FWD_CFG_CPU_IGMP_REDIR_ENA ; 
 int ANA_PORT_CPU_FWD_CFG_CPU_IPMC_CTRL_COPY_ENA ; 
 int ANA_PORT_CPU_FWD_CFG_CPU_MLD_REDIR_ENA ; 
 int ocelot_read_gix (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write_gix (struct ocelot*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocelot_port_attr_mc_set(struct ocelot_port *port, bool mc)
{
	struct ocelot *ocelot = port->ocelot;
	u32 val = ocelot_read_gix(ocelot, ANA_PORT_CPU_FWD_CFG,
				  port->chip_port);

	if (mc)
		val |= ANA_PORT_CPU_FWD_CFG_CPU_IGMP_REDIR_ENA |
		       ANA_PORT_CPU_FWD_CFG_CPU_MLD_REDIR_ENA |
		       ANA_PORT_CPU_FWD_CFG_CPU_IPMC_CTRL_COPY_ENA;
	else
		val &= ~(ANA_PORT_CPU_FWD_CFG_CPU_IGMP_REDIR_ENA |
			 ANA_PORT_CPU_FWD_CFG_CPU_MLD_REDIR_ENA |
			 ANA_PORT_CPU_FWD_CFG_CPU_IPMC_CTRL_COPY_ENA);

	ocelot_write_gix(ocelot, val, ANA_PORT_CPU_FWD_CFG, port->chip_port);
}