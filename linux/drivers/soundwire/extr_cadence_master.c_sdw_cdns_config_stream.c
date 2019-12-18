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
typedef  scalar_t__ u32 ;
struct sdw_cdns_port {int num; } ;
struct sdw_cdns_pdi {int /*<<< orphan*/  num; } ;
struct sdw_cdns {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_PDI_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDNS_PDI_CONFIG_CHANNEL ; 
 scalar_t__ CDNS_PORTCTRL ; 
 scalar_t__ CDNS_PORTCTRL_DIRN ; 
 int CDNS_PORT_OFFSET ; 
 scalar_t__ SDW_DATA_DIR_RX ; 
 int SDW_REG_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_updatel (struct sdw_cdns*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int /*<<< orphan*/ ,scalar_t__) ; 

void sdw_cdns_config_stream(struct sdw_cdns *cdns,
			    struct sdw_cdns_port *port,
			    u32 ch, u32 dir, struct sdw_cdns_pdi *pdi)
{
	u32 offset, val = 0;

	if (dir == SDW_DATA_DIR_RX)
		val = CDNS_PORTCTRL_DIRN;

	offset = CDNS_PORTCTRL + port->num * CDNS_PORT_OFFSET;
	cdns_updatel(cdns, offset, CDNS_PORTCTRL_DIRN, val);

	val = port->num;
	val |= ((1 << ch) - 1) << SDW_REG_SHIFT(CDNS_PDI_CONFIG_CHANNEL);
	cdns_writel(cdns, CDNS_PDI_CONFIG(pdi->num), val);
}