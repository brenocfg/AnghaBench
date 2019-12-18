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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct hns_roce_dev {TYPE_1__* hw; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* chk_mbox ) (struct hns_roce_dev*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_POLL_TOKEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hns_roce_cmd_mbox_post_hw (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct hns_roce_dev*,unsigned long) ; 

__attribute__((used)) static int __hns_roce_cmd_mbox_poll(struct hns_roce_dev *hr_dev, u64 in_param,
				    u64 out_param, unsigned long in_modifier,
				    u8 op_modifier, u16 op,
				    unsigned long timeout)
{
	struct device *dev = hr_dev->dev;
	int ret;

	ret = hns_roce_cmd_mbox_post_hw(hr_dev, in_param, out_param,
					in_modifier, op_modifier, op,
					CMD_POLL_TOKEN, 0);
	if (ret) {
		dev_err(dev, "[cmd_poll]hns_roce_cmd_mbox_post_hw failed\n");
		return ret;
	}

	return hr_dev->hw->chk_mbox(hr_dev, timeout);
}