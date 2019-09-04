#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct be_port_resources {int nic_pfs; int max_vfs; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int max_rss_tables; } ;
struct be_adapter {TYPE_1__ pool_res; } ;

/* Variables and functions */
 int MAX_PORT_RSS_TABLES ; 
 int /*<<< orphan*/  RESOURCE_LIMITS ; 
 int /*<<< orphan*/  SAVED_PROFILE_TYPE ; 
 int /*<<< orphan*/  be_cmd_get_profile_config (struct be_adapter*,int /*<<< orphan*/ *,struct be_port_resources*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_max_vfs (struct be_adapter*) ; 

__attribute__((used)) static void be_calculate_pf_pool_rss_tables(struct be_adapter *adapter)
{
	struct be_port_resources port_res = {0};
	u8 rss_tables_on_port;
	u16 max_vfs = be_max_vfs(adapter);

	be_cmd_get_profile_config(adapter, NULL, &port_res, SAVED_PROFILE_TYPE,
				  RESOURCE_LIMITS, 0);

	rss_tables_on_port = MAX_PORT_RSS_TABLES - port_res.nic_pfs;

	/* Each PF Pool's RSS Tables limit =
	 * PF's Max VFs / Total_Max_VFs on Port * RSS Tables on Port
	 */
	adapter->pool_res.max_rss_tables =
		max_vfs * rss_tables_on_port / port_res.max_vfs;
}