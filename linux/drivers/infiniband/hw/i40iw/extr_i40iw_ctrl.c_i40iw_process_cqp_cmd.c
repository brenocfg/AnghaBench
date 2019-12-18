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
struct i40iw_sc_dev {int /*<<< orphan*/  cqp_lock; int /*<<< orphan*/  cqp_cmd_head; int /*<<< orphan*/  cqp; } ;
struct cqp_commands_info {int /*<<< orphan*/  cqp_cmd_entry; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int i40iw_exec_cqp_cmd (struct i40iw_sc_dev*,struct cqp_commands_info*) ; 
 int /*<<< orphan*/  i40iw_ring_full (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

enum i40iw_status_code i40iw_process_cqp_cmd(struct i40iw_sc_dev *dev,
					     struct cqp_commands_info *pcmdinfo)
{
	enum i40iw_status_code status = 0;
	unsigned long flags;

	spin_lock_irqsave(&dev->cqp_lock, flags);
	if (list_empty(&dev->cqp_cmd_head) && !i40iw_ring_full(dev->cqp))
		status = i40iw_exec_cqp_cmd(dev, pcmdinfo);
	else
		list_add_tail(&pcmdinfo->cqp_cmd_entry, &dev->cqp_cmd_head);
	spin_unlock_irqrestore(&dev->cqp_lock, flags);
	return status;
}