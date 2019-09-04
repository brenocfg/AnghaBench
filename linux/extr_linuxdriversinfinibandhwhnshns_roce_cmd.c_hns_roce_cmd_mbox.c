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
struct TYPE_2__ {scalar_t__ use_events; } ;
struct hns_roce_dev {TYPE_1__ cmd; scalar_t__ is_reset; } ;

/* Variables and functions */
 int hns_roce_cmd_mbox_poll (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int hns_roce_cmd_mbox_wait (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

int hns_roce_cmd_mbox(struct hns_roce_dev *hr_dev, u64 in_param, u64 out_param,
		      unsigned long in_modifier, u8 op_modifier, u16 op,
		      unsigned long timeout)
{
	if (hr_dev->is_reset)
		return 0;

	if (hr_dev->cmd.use_events)
		return hns_roce_cmd_mbox_wait(hr_dev, in_param, out_param,
					      in_modifier, op_modifier, op,
					      timeout);
	else
		return hns_roce_cmd_mbox_poll(hr_dev, in_param, out_param,
					      in_modifier, op_modifier, op,
					      timeout);
}