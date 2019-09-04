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
typedef  int /*<<< orphan*/  u16 ;
struct qede_dev {int /*<<< orphan*/  cdev; TYPE_1__* ops; } ;
struct TYPE_5__ {int type; int vlan_valid; int /*<<< orphan*/  vlan; } ;
struct TYPE_6__ {TYPE_2__ ucast; } ;
struct qed_filter_params {TYPE_3__ filter; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  filter_cmd ;
typedef  enum qed_filter_xcast_params_type { ____Placeholder_qed_filter_xcast_params_type } qed_filter_xcast_params_type ;
struct TYPE_4__ {int (* filter_config ) (int /*<<< orphan*/ ,struct qed_filter_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QED_FILTER_TYPE_UCAST ; 
 int /*<<< orphan*/  memset (struct qed_filter_params*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct qed_filter_params*) ; 

__attribute__((used)) static int qede_set_ucast_rx_vlan(struct qede_dev *edev,
				  enum qed_filter_xcast_params_type opcode,
				  u16 vid)
{
	struct qed_filter_params filter_cmd;

	memset(&filter_cmd, 0, sizeof(filter_cmd));
	filter_cmd.type = QED_FILTER_TYPE_UCAST;
	filter_cmd.filter.ucast.type = opcode;
	filter_cmd.filter.ucast.vlan_valid = 1;
	filter_cmd.filter.ucast.vlan = vid;

	return edev->ops->filter_config(edev->cdev, &filter_cmd);
}