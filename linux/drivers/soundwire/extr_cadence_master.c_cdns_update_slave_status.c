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
typedef  int u64 ;
typedef  int u32 ;
struct sdw_cdns {int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  status ;
typedef  enum sdw_slave_status { ____Placeholder_sdw_slave_status } sdw_slave_status ;

/* Variables and functions */
 int CDNS_MCP_SLAVE_INTSTAT_ALERT ; 
 int CDNS_MCP_SLAVE_INTSTAT_ATTACHED ; 
 int CDNS_MCP_SLAVE_INTSTAT_NPRESENT ; 
 int CDNS_MCP_SLAVE_INTSTAT_RESERVED ; 
 int CDNS_MCP_SLAVE_STATUS_BITS ; 
 int CDNS_MCP_SLAVE_STATUS_NUM ; 
 int SDW_MAX_DEVICES ; 
 int SDW_SLAVE_ALERT ; 
 int SDW_SLAVE_ATTACHED ; 
 int SDW_SLAVE_RESERVED ; 
 int SDW_SLAVE_UNATTACHED ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int sdw_handle_slave_status (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int cdns_update_slave_status(struct sdw_cdns *cdns,
				    u32 slave0, u32 slave1)
{
	enum sdw_slave_status status[SDW_MAX_DEVICES + 1];
	bool is_slave = false;
	u64 slave;
	u32 mask;
	int i, set_status;

	/* combine the two status */
	slave = ((u64)slave1 << 32) | slave0;
	memset(status, 0, sizeof(status));

	for (i = 0; i <= SDW_MAX_DEVICES; i++) {
		mask = (slave >> (i * CDNS_MCP_SLAVE_STATUS_NUM)) &
				CDNS_MCP_SLAVE_STATUS_BITS;
		if (!mask)
			continue;

		is_slave = true;
		set_status = 0;

		if (mask & CDNS_MCP_SLAVE_INTSTAT_RESERVED) {
			status[i] = SDW_SLAVE_RESERVED;
			set_status++;
		}

		if (mask & CDNS_MCP_SLAVE_INTSTAT_ATTACHED) {
			status[i] = SDW_SLAVE_ATTACHED;
			set_status++;
		}

		if (mask & CDNS_MCP_SLAVE_INTSTAT_ALERT) {
			status[i] = SDW_SLAVE_ALERT;
			set_status++;
		}

		if (mask & CDNS_MCP_SLAVE_INTSTAT_NPRESENT) {
			status[i] = SDW_SLAVE_UNATTACHED;
			set_status++;
		}

		/* first check if Slave reported multiple status */
		if (set_status > 1) {
			dev_warn_ratelimited(cdns->dev,
					     "Slave reported multiple Status: %d\n",
					     mask);
			/*
			 * TODO: we need to reread the status here by
			 * issuing a PING cmd
			 */
		}
	}

	if (is_slave)
		return sdw_handle_slave_status(&cdns->bus, status);

	return 0;
}