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
struct hns_roce_v2_priv {struct hnae3_handle* handle; } ;
struct hns_roce_dev {int dis_db; int is_reset; scalar_t__ priv; } ;
struct hnae3_handle {TYPE_1__* ae_algo; } ;
struct hnae3_ae_ops {int /*<<< orphan*/  (* get_hw_reset_stat ) (struct hnae3_handle*) ;} ;
struct TYPE_2__ {struct hnae3_ae_ops* ops; } ;

/* Variables and functions */
 int CMD_RST_PRC_EBUSY ; 
 int CMD_RST_PRC_SUCCESS ; 
 unsigned long HNS_ROCE_STATE_INIT ; 
 unsigned long HNS_ROCE_STATE_RST_INIT ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*) ; 

__attribute__((used)) static int hns_roce_v2_cmd_hw_resetting(struct hns_roce_dev *hr_dev,
					unsigned long instance_stage,
					unsigned long reset_stage)
{
	struct hns_roce_v2_priv *priv = (struct hns_roce_v2_priv *)hr_dev->priv;
	struct hnae3_handle *handle = priv->handle;
	const struct hnae3_ae_ops *ops = handle->ae_algo->ops;

	/* When hardware reset is detected, we should stop sending mailbox&cmq&
	 * doorbell to hardware. If now in .init_instance() function, we should
	 * exit with error. If now at HNAE3_INIT_CLIENT stage of soft reset
	 * process, we should exit with error, and then HNAE3_INIT_CLIENT
	 * related process can rollback the operation like notifing hardware to
	 * free resources, HNAE3_INIT_CLIENT related process will exit with
	 * error to notify NIC driver to reschedule soft reset process once
	 * again.
	 */
	hr_dev->dis_db = true;
	if (!ops->get_hw_reset_stat(handle))
		hr_dev->is_reset = true;

	if (!hr_dev->is_reset || reset_stage == HNS_ROCE_STATE_RST_INIT ||
	    instance_stage == HNS_ROCE_STATE_INIT)
		return CMD_RST_PRC_EBUSY;

	return CMD_RST_PRC_SUCCESS;
}