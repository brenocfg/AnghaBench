#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_3__* ops; } ;
struct TYPE_4__ {int type; int num; int /*<<< orphan*/ * mac; } ;
struct TYPE_5__ {TYPE_1__ mcast; } ;
struct qed_filter_params {TYPE_2__ filter; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  filter_cmd ;
typedef  enum qed_filter_xcast_params_type { ____Placeholder_qed_filter_xcast_params_type } qed_filter_xcast_params_type ;
struct TYPE_6__ {int (* filter_config ) (int /*<<< orphan*/ ,struct qed_filter_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  QED_FILTER_TYPE_MCAST ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  memset (struct qed_filter_params*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct qed_filter_params*) ; 

__attribute__((used)) static int qede_set_mcast_rx_mac(struct qede_dev *edev,
				 enum qed_filter_xcast_params_type opcode,
				 unsigned char *mac, int num_macs)
{
	struct qed_filter_params filter_cmd;
	int i;

	memset(&filter_cmd, 0, sizeof(filter_cmd));
	filter_cmd.type = QED_FILTER_TYPE_MCAST;
	filter_cmd.filter.mcast.type = opcode;
	filter_cmd.filter.mcast.num = num_macs;

	for (i = 0; i < num_macs; i++, mac += ETH_ALEN)
		ether_addr_copy(filter_cmd.filter.mcast.mac[i], mac);

	return edev->ops->filter_config(edev->cdev, &filter_cmd);
}