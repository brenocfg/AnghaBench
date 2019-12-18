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
struct hns_roce_dev {unsigned long reset_cnt; scalar_t__ priv; } ;
struct hnae3_handle {TYPE_1__* ae_algo; } ;
struct hnae3_ae_ops {unsigned long (* ae_dev_reset_cnt ) (struct hnae3_handle*) ;int (* get_hw_reset_stat ) (struct hnae3_handle*) ;int (* ae_dev_resetting ) (struct hnae3_handle*) ;} ;
struct TYPE_2__ {struct hnae3_ae_ops* ops; } ;

/* Variables and functions */
 unsigned long stub1 (struct hnae3_handle*) ; 
 int stub2 (struct hnae3_handle*) ; 
 int stub3 (struct hnae3_handle*) ; 

__attribute__((used)) static bool hns_roce_func_clr_chk_rst(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_v2_priv *priv = (struct hns_roce_v2_priv *)hr_dev->priv;
	struct hnae3_handle *handle = priv->handle;
	const struct hnae3_ae_ops *ops = handle->ae_algo->ops;
	unsigned long reset_cnt;
	bool sw_resetting;
	bool hw_resetting;

	reset_cnt = ops->ae_dev_reset_cnt(handle);
	hw_resetting = ops->get_hw_reset_stat(handle);
	sw_resetting = ops->ae_dev_resetting(handle);

	if (reset_cnt != hr_dev->reset_cnt || hw_resetting || sw_resetting)
		return true;

	return false;
}