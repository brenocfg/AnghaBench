#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hns_roce_v2_priv {struct hnae3_handle* handle; } ;
struct hns_roce_dev {unsigned long reset_cnt; scalar_t__ is_reset; scalar_t__ priv; } ;
struct TYPE_4__ {unsigned long instance_state; unsigned long reset_state; } ;
struct hnae3_handle {TYPE_2__ rinfo; TYPE_1__* ae_algo; } ;
struct hnae3_ae_ops {unsigned long (* ae_dev_reset_cnt ) (struct hnae3_handle*) ;int (* get_hw_reset_stat ) (struct hnae3_handle*) ;int (* ae_dev_resetting ) (struct hnae3_handle*) ;} ;
struct TYPE_3__ {struct hnae3_ae_ops* ops; } ;

/* Variables and functions */
 int CMD_RST_PRC_SUCCESS ; 
 unsigned long HNS_ROCE_STATE_INIT ; 
 int hns_roce_v2_cmd_hw_reseted (struct hns_roce_dev*,unsigned long,unsigned long) ; 
 int hns_roce_v2_cmd_hw_resetting (struct hns_roce_dev*,unsigned long,unsigned long) ; 
 int hns_roce_v2_cmd_sw_resetting (struct hns_roce_dev*) ; 
 unsigned long stub1 (struct hnae3_handle*) ; 
 int stub2 (struct hnae3_handle*) ; 
 int stub3 (struct hnae3_handle*) ; 

__attribute__((used)) static int hns_roce_v2_rst_process_cmd(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_v2_priv *priv = (struct hns_roce_v2_priv *)hr_dev->priv;
	struct hnae3_handle *handle = priv->handle;
	const struct hnae3_ae_ops *ops = handle->ae_algo->ops;
	unsigned long instance_stage;	/* the current instance stage */
	unsigned long reset_stage;	/* the current reset stage */
	unsigned long reset_cnt;
	bool sw_resetting;
	bool hw_resetting;

	if (hr_dev->is_reset)
		return CMD_RST_PRC_SUCCESS;

	/* Get information about reset from NIC driver or RoCE driver itself,
	 * the meaning of the following variables from NIC driver are described
	 * as below:
	 * reset_cnt -- The count value of completed hardware reset.
	 * hw_resetting -- Whether hardware device is resetting now.
	 * sw_resetting -- Whether NIC's software reset process is running now.
	 */
	instance_stage = handle->rinfo.instance_state;
	reset_stage = handle->rinfo.reset_state;
	reset_cnt = ops->ae_dev_reset_cnt(handle);
	hw_resetting = ops->get_hw_reset_stat(handle);
	sw_resetting = ops->ae_dev_resetting(handle);

	if (reset_cnt != hr_dev->reset_cnt)
		return hns_roce_v2_cmd_hw_reseted(hr_dev, instance_stage,
						  reset_stage);
	else if (hw_resetting)
		return hns_roce_v2_cmd_hw_resetting(hr_dev, instance_stage,
						    reset_stage);
	else if (sw_resetting && instance_stage == HNS_ROCE_STATE_INIT)
		return hns_roce_v2_cmd_sw_resetting(hr_dev);

	return 0;
}