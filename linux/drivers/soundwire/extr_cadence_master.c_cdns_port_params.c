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
struct sdw_port_params {int bps; int flow_mode; int data_mode; int /*<<< orphan*/  num; } ;
struct sdw_cdns {int dummy; } ;
struct sdw_bus {int dummy; } ;

/* Variables and functions */
 int CDNS_DPN_B0_CONFIG (int /*<<< orphan*/ ) ; 
 int CDNS_DPN_B1_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDNS_DPN_CONFIG_PORT_DAT ; 
 int /*<<< orphan*/  CDNS_DPN_CONFIG_PORT_FLOW ; 
 int /*<<< orphan*/  CDNS_DPN_CONFIG_WL ; 
 int SDW_REG_SHIFT (int /*<<< orphan*/ ) ; 
 struct sdw_cdns* bus_to_cdns (struct sdw_bus*) ; 
 int cdns_readl (struct sdw_cdns*,int) ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int,int) ; 

__attribute__((used)) static int cdns_port_params(struct sdw_bus *bus,
			    struct sdw_port_params *p_params, unsigned int bank)
{
	struct sdw_cdns *cdns = bus_to_cdns(bus);
	int dpn_config = 0, dpn_config_off;

	if (bank)
		dpn_config_off = CDNS_DPN_B1_CONFIG(p_params->num);
	else
		dpn_config_off = CDNS_DPN_B0_CONFIG(p_params->num);

	dpn_config = cdns_readl(cdns, dpn_config_off);

	dpn_config |= ((p_params->bps - 1) <<
				SDW_REG_SHIFT(CDNS_DPN_CONFIG_WL));
	dpn_config |= (p_params->flow_mode <<
				SDW_REG_SHIFT(CDNS_DPN_CONFIG_PORT_FLOW));
	dpn_config |= (p_params->data_mode <<
				SDW_REG_SHIFT(CDNS_DPN_CONFIG_PORT_DAT));

	cdns_writel(cdns, dpn_config_off, dpn_config);

	return 0;
}