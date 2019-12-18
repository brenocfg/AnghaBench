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
struct ocelot {int dummy; } ;

/* Variables and functions */
 int ANA_TABLES_VLANACCESS_CMD_IDLE ; 
 int ANA_TABLES_VLANACCESS_VLAN_TBL_CMD_M ; 
 int /*<<< orphan*/  TABLE_UPDATE_SLEEP_US ; 
 int /*<<< orphan*/  TABLE_UPDATE_TIMEOUT_US ; 
 int /*<<< orphan*/  ocelot_vlant_read_vlanaccess ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct ocelot*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocelot_vlant_wait_for_completion(struct ocelot *ocelot)
{
	u32 val;

	return readx_poll_timeout(ocelot_vlant_read_vlanaccess,
		ocelot,
		val,
		(val & ANA_TABLES_VLANACCESS_VLAN_TBL_CMD_M) ==
		ANA_TABLES_VLANACCESS_CMD_IDLE,
		TABLE_UPDATE_SLEEP_US, TABLE_UPDATE_TIMEOUT_US);
}