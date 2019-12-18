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
struct sdw_cdns {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_MCP_CONFIG_UPDATE ; 
 int /*<<< orphan*/  CDNS_MCP_CONFIG_UPDATE_BIT ; 
 int /*<<< orphan*/  _cdns_enable_interrupt (struct sdw_cdns*) ; 
 int cdns_clear_bit (struct sdw_cdns*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

int sdw_cdns_enable_interrupt(struct sdw_cdns *cdns)
{
	int ret;

	_cdns_enable_interrupt(cdns);
	ret = cdns_clear_bit(cdns, CDNS_MCP_CONFIG_UPDATE,
			     CDNS_MCP_CONFIG_UPDATE_BIT);
	if (ret < 0)
		dev_err(cdns->dev, "Config update timedout\n");

	return ret;
}