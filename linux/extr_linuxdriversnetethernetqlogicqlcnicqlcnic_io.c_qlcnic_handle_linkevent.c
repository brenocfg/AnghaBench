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
typedef  int u32 ;
typedef  int u16 ;
struct qlcnic_fw_msg {int* body; } ;
struct qlcnic_adapter {TYPE_1__* ahw; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int has_link_events; int module_type; int link_autoneg; int link_speed; int /*<<< orphan*/  link_duplex; int /*<<< orphan*/  loopback_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int LINKEVENT_FULL_DUPLEX ; 
 int LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLE ; 
 int LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLELEN ; 
 int QLCNIC_ELB_MODE ; 
 int QLCNIC_ILB_MODE ; 
 int /*<<< orphan*/  QLCNIC_LINKEVENT ; 
 int SPEED_UNKNOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  qlcnic_advert_link_change (struct qlcnic_adapter*,int) ; 

__attribute__((used)) static void qlcnic_handle_linkevent(struct qlcnic_adapter *adapter,
				    struct qlcnic_fw_msg *msg)
{
	u32 cable_OUI;
	u16 cable_len, link_speed;
	u8  link_status, module, duplex, autoneg, lb_status = 0;
	struct net_device *netdev = adapter->netdev;

	adapter->ahw->has_link_events = 1;

	cable_OUI = msg->body[1] & 0xffffffff;
	cable_len = (msg->body[1] >> 32) & 0xffff;
	link_speed = (msg->body[1] >> 48) & 0xffff;

	link_status = msg->body[2] & 0xff;
	duplex = (msg->body[2] >> 16) & 0xff;
	autoneg = (msg->body[2] >> 24) & 0xff;
	lb_status = (msg->body[2] >> 32) & 0x3;

	module = (msg->body[2] >> 8) & 0xff;
	if (module == LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLE)
		dev_info(&netdev->dev,
			 "unsupported cable: OUI 0x%x, length %d\n",
			 cable_OUI, cable_len);
	else if (module == LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLELEN)
		dev_info(&netdev->dev, "unsupported cable length %d\n",
			 cable_len);

	if (!link_status && (lb_status == QLCNIC_ILB_MODE ||
	    lb_status == QLCNIC_ELB_MODE))
		adapter->ahw->loopback_state |= QLCNIC_LINKEVENT;

	qlcnic_advert_link_change(adapter, link_status);

	if (duplex == LINKEVENT_FULL_DUPLEX)
		adapter->ahw->link_duplex = DUPLEX_FULL;
	else
		adapter->ahw->link_duplex = DUPLEX_HALF;

	adapter->ahw->module_type = module;
	adapter->ahw->link_autoneg = autoneg;

	if (link_status) {
		adapter->ahw->link_speed = link_speed;
	} else {
		adapter->ahw->link_speed = SPEED_UNKNOWN;
		adapter->ahw->link_duplex = DUPLEX_UNKNOWN;
	}
}