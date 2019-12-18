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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ board_type; } ;
struct netxen_adapter {TYPE_1__ ahw; } ;

/* Variables and functions */
 scalar_t__ NETXEN_BRDTYPE_P3_HMEZ ; 
 scalar_t__ NETXEN_BRDTYPE_P3_XG_LOM ; 
 scalar_t__ NETXEN_PORT_MODE_802_3_AP ; 
 int /*<<< orphan*/  NETXEN_PORT_MODE_ADDR ; 
 scalar_t__ NETXEN_PORT_MODE_AUTO_NEG ; 
 scalar_t__ NETXEN_PORT_MODE_AUTO_NEG_1G ; 
 scalar_t__ NETXEN_PORT_MODE_AUTO_NEG_XG ; 
 scalar_t__ NETXEN_PORT_MODE_XG ; 
 int /*<<< orphan*/  NETXEN_WOL_PORT_MODE ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ port_mode ; 
 scalar_t__ wol_port_mode ; 

__attribute__((used)) static void netxen_set_port_mode(struct netxen_adapter *adapter)
{
	u32 val, data;

	val = adapter->ahw.board_type;
	if ((val == NETXEN_BRDTYPE_P3_HMEZ) ||
		(val == NETXEN_BRDTYPE_P3_XG_LOM)) {
		if (port_mode == NETXEN_PORT_MODE_802_3_AP) {
			data = NETXEN_PORT_MODE_802_3_AP;
			NXWR32(adapter, NETXEN_PORT_MODE_ADDR, data);
		} else if (port_mode == NETXEN_PORT_MODE_XG) {
			data = NETXEN_PORT_MODE_XG;
			NXWR32(adapter, NETXEN_PORT_MODE_ADDR, data);
		} else if (port_mode == NETXEN_PORT_MODE_AUTO_NEG_1G) {
			data = NETXEN_PORT_MODE_AUTO_NEG_1G;
			NXWR32(adapter, NETXEN_PORT_MODE_ADDR, data);
		} else if (port_mode == NETXEN_PORT_MODE_AUTO_NEG_XG) {
			data = NETXEN_PORT_MODE_AUTO_NEG_XG;
			NXWR32(adapter, NETXEN_PORT_MODE_ADDR, data);
		} else {
			data = NETXEN_PORT_MODE_AUTO_NEG;
			NXWR32(adapter, NETXEN_PORT_MODE_ADDR, data);
		}

		if ((wol_port_mode != NETXEN_PORT_MODE_802_3_AP) &&
			(wol_port_mode != NETXEN_PORT_MODE_XG) &&
			(wol_port_mode != NETXEN_PORT_MODE_AUTO_NEG_1G) &&
			(wol_port_mode != NETXEN_PORT_MODE_AUTO_NEG_XG)) {
			wol_port_mode = NETXEN_PORT_MODE_AUTO_NEG;
		}
		NXWR32(adapter, NETXEN_WOL_PORT_MODE, wol_port_mode);
	}
}