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
struct hns_roce_cmdq {scalar_t__ use_events; int /*<<< orphan*/  context; } ;
struct hns_roce_dev {struct hns_roce_cmdq cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void hns_roce_cmd_use_polling(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_cmdq *hr_cmd = &hr_dev->cmd;

	kfree(hr_cmd->context);
	hr_cmd->use_events = 0;
}