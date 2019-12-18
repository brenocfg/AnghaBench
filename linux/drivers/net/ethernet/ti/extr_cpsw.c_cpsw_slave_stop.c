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
typedef  int /*<<< orphan*/  u32 ;
struct cpsw_slave {int /*<<< orphan*/  mac_sl; int /*<<< orphan*/ * phy; int /*<<< orphan*/  slave_num; } ;
struct cpsw_common {int /*<<< orphan*/  ale; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_PORT_STATE ; 
 int /*<<< orphan*/  ALE_PORT_STATE_DISABLE ; 
 int /*<<< orphan*/  cpsw_ale_control_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_get_slave_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_sl_ctl_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_sl_reset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpsw_slave_stop(struct cpsw_slave *slave, struct cpsw_common *cpsw)
{
	u32 slave_port;

	slave_port = cpsw_get_slave_port(slave->slave_num);

	if (!slave->phy)
		return;
	phy_stop(slave->phy);
	phy_disconnect(slave->phy);
	slave->phy = NULL;
	cpsw_ale_control_set(cpsw->ale, slave_port,
			     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);
	cpsw_sl_reset(slave->mac_sl, 100);
	cpsw_sl_ctl_reset(slave->mac_sl);
}