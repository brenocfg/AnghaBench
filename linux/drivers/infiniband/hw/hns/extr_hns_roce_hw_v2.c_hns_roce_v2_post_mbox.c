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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hns_roce_dev {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  HNS_ROCE_V2_GO_BIT_TIMEOUT_MSECS ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int hns_roce_mbox_post (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hns_roce_v2_cmd_pending (struct hns_roce_dev*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int hns_roce_v2_post_mbox(struct hns_roce_dev *hr_dev, u64 in_param,
				 u64 out_param, u32 in_modifier, u8 op_modifier,
				 u16 op, u16 token, int event)
{
	struct device *dev = hr_dev->dev;
	unsigned long end;
	int ret;

	end = msecs_to_jiffies(HNS_ROCE_V2_GO_BIT_TIMEOUT_MSECS) + jiffies;
	while (hns_roce_v2_cmd_pending(hr_dev)) {
		if (time_after(jiffies, end)) {
			dev_dbg(dev, "jiffies=%d end=%d\n", (int)jiffies,
				(int)end);
			return -EAGAIN;
		}
		cond_resched();
	}

	ret = hns_roce_mbox_post(hr_dev, in_param, out_param, in_modifier,
				 op_modifier, op, token, event);
	if (ret)
		dev_err(dev, "Post mailbox fail(%d)\n", ret);

	return ret;
}