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
struct hns_roce_dev {unsigned long reset_cnt; int dis_db; int is_reset; int /*<<< orphan*/  dev; scalar_t__ priv; } ;
struct TYPE_4__ {unsigned long instance_state; } ;
struct hnae3_handle {TYPE_2__ rinfo; TYPE_1__* ae_algo; } ;
struct hnae3_ae_ops {unsigned long (* ae_dev_reset_cnt ) (struct hnae3_handle*) ;int (* get_hw_reset_stat ) (struct hnae3_handle*) ;int (* ae_dev_resetting ) (struct hnae3_handle*) ;} ;
struct TYPE_3__ {struct hnae3_ae_ops* ops; } ;

/* Variables and functions */
 unsigned long HNS_ROCE_STATE_INIT ; 
 scalar_t__ HNS_ROCE_V2_HW_RST_COMPLETION_WAIT ; 
 unsigned long HNS_ROCE_V2_HW_RST_TIMEOUT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 unsigned long stub1 (struct hnae3_handle*) ; 
 int stub2 (struct hnae3_handle*) ; 
 int stub3 (struct hnae3_handle*) ; 
 int stub4 (struct hnae3_handle*) ; 
 unsigned long stub5 (struct hnae3_handle*) ; 

__attribute__((used)) static void hns_roce_func_clr_rst_prc(struct hns_roce_dev *hr_dev, int retval,
				      int flag)
{
	struct hns_roce_v2_priv *priv = (struct hns_roce_v2_priv *)hr_dev->priv;
	struct hnae3_handle *handle = priv->handle;
	const struct hnae3_ae_ops *ops = handle->ae_algo->ops;
	unsigned long instance_stage;
	unsigned long reset_cnt;
	unsigned long end;
	bool sw_resetting;
	bool hw_resetting;

	instance_stage = handle->rinfo.instance_state;
	reset_cnt = ops->ae_dev_reset_cnt(handle);
	hw_resetting = ops->get_hw_reset_stat(handle);
	sw_resetting = ops->ae_dev_resetting(handle);

	if (reset_cnt != hr_dev->reset_cnt) {
		hr_dev->dis_db = true;
		hr_dev->is_reset = true;
		dev_info(hr_dev->dev, "Func clear success after reset.\n");
	} else if (hw_resetting) {
		hr_dev->dis_db = true;

		dev_warn(hr_dev->dev,
			 "Func clear is pending, device in resetting state.\n");
		end = HNS_ROCE_V2_HW_RST_TIMEOUT;
		while (end) {
			if (!ops->get_hw_reset_stat(handle)) {
				hr_dev->is_reset = true;
				dev_info(hr_dev->dev,
					 "Func clear success after reset.\n");
				return;
			}
			msleep(HNS_ROCE_V2_HW_RST_COMPLETION_WAIT);
			end -= HNS_ROCE_V2_HW_RST_COMPLETION_WAIT;
		}

		dev_warn(hr_dev->dev, "Func clear failed.\n");
	} else if (sw_resetting && instance_stage == HNS_ROCE_STATE_INIT) {
		hr_dev->dis_db = true;

		dev_warn(hr_dev->dev,
			 "Func clear is pending, device in resetting state.\n");
		end = HNS_ROCE_V2_HW_RST_TIMEOUT;
		while (end) {
			if (ops->ae_dev_reset_cnt(handle) !=
			    hr_dev->reset_cnt) {
				hr_dev->is_reset = true;
				dev_info(hr_dev->dev,
					 "Func clear success after sw reset\n");
				return;
			}
			msleep(HNS_ROCE_V2_HW_RST_COMPLETION_WAIT);
			end -= HNS_ROCE_V2_HW_RST_COMPLETION_WAIT;
		}

		dev_warn(hr_dev->dev, "Func clear failed because of unfinished sw reset\n");
	} else {
		if (retval && !flag)
			dev_warn(hr_dev->dev,
				 "Func clear read failed, ret = %d.\n", retval);

		dev_warn(hr_dev->dev, "Func clear failed.\n");
	}
}