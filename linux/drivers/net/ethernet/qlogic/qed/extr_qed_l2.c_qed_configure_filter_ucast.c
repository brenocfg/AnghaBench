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
typedef  int /*<<< orphan*/  ucast ;
struct qed_filter_ucast_params {int type; int /*<<< orphan*/  vlan; int /*<<< orphan*/  mac; scalar_t__ mac_valid; scalar_t__ vlan_valid; } ;
struct qed_filter_ucast {int is_rx_filter; int is_tx_filter; int /*<<< orphan*/  vlan; int /*<<< orphan*/  type; int /*<<< orphan*/  mac; int /*<<< orphan*/  opcode; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_FILTER_ADD ; 
 int /*<<< orphan*/  QED_FILTER_MAC ; 
 int /*<<< orphan*/  QED_FILTER_MAC_VLAN ; 
 int /*<<< orphan*/  QED_FILTER_REMOVE ; 
 int /*<<< orphan*/  QED_FILTER_REPLACE ; 
 int /*<<< orphan*/  QED_FILTER_VLAN ; 
#define  QED_FILTER_XCAST_TYPE_ADD 130 
#define  QED_FILTER_XCAST_TYPE_DEL 129 
#define  QED_FILTER_XCAST_TYPE_REPLACE 128 
 int /*<<< orphan*/  QED_SPQ_MODE_CB ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_filter_ucast*,int /*<<< orphan*/ ,int) ; 
 int qed_filter_ucast_cmd (struct qed_dev*,struct qed_filter_ucast*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_configure_filter_ucast(struct qed_dev *cdev,
				      struct qed_filter_ucast_params *params)
{
	struct qed_filter_ucast ucast;

	if (!params->vlan_valid && !params->mac_valid) {
		DP_NOTICE(cdev,
			  "Tried configuring a unicast filter, but both MAC and VLAN are not set\n");
		return -EINVAL;
	}

	memset(&ucast, 0, sizeof(ucast));
	switch (params->type) {
	case QED_FILTER_XCAST_TYPE_ADD:
		ucast.opcode = QED_FILTER_ADD;
		break;
	case QED_FILTER_XCAST_TYPE_DEL:
		ucast.opcode = QED_FILTER_REMOVE;
		break;
	case QED_FILTER_XCAST_TYPE_REPLACE:
		ucast.opcode = QED_FILTER_REPLACE;
		break;
	default:
		DP_NOTICE(cdev, "Unknown unicast filter type %d\n",
			  params->type);
	}

	if (params->vlan_valid && params->mac_valid) {
		ucast.type = QED_FILTER_MAC_VLAN;
		ether_addr_copy(ucast.mac, params->mac);
		ucast.vlan = params->vlan;
	} else if (params->mac_valid) {
		ucast.type = QED_FILTER_MAC;
		ether_addr_copy(ucast.mac, params->mac);
	} else {
		ucast.type = QED_FILTER_VLAN;
		ucast.vlan = params->vlan;
	}

	ucast.is_rx_filter = true;
	ucast.is_tx_filter = true;

	return qed_filter_ucast_cmd(cdev, &ucast, QED_SPQ_MODE_CB, NULL);
}