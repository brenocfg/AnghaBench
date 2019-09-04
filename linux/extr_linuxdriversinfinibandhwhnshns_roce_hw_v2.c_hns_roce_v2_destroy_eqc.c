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
struct TYPE_2__ {int num_comp_vectors; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_CMD_DESTROY_AEQC ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_DESTROY_CEQC ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_TIMEOUT_MSECS ; 
 int HNS_ROCE_V2_EQN_M ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int hns_roce_cmd_mbox (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_v2_destroy_eqc(struct hns_roce_dev *hr_dev, int eqn)
{
	struct device *dev = hr_dev->dev;
	int ret;

	if (eqn < hr_dev->caps.num_comp_vectors)
		ret = hns_roce_cmd_mbox(hr_dev, 0, 0, eqn & HNS_ROCE_V2_EQN_M,
					0, HNS_ROCE_CMD_DESTROY_CEQC,
					HNS_ROCE_CMD_TIMEOUT_MSECS);
	else
		ret = hns_roce_cmd_mbox(hr_dev, 0, 0, eqn & HNS_ROCE_V2_EQN_M,
					0, HNS_ROCE_CMD_DESTROY_AEQC,
					HNS_ROCE_CMD_TIMEOUT_MSECS);
	if (ret)
		dev_err(dev, "[mailbox cmd] destroy eqc(%d) failed.\n", eqn);
}