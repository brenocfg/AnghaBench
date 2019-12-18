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
struct pqi_io_request {int /*<<< orphan*/  request_list_entry; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  raid_bypass_retry_list_lock; int /*<<< orphan*/  raid_bypass_retry_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void pqi_add_to_raid_bypass_retry_list(
	struct pqi_ctrl_info *ctrl_info,
	struct pqi_io_request *io_request, bool at_head)
{
	unsigned long flags;

	spin_lock_irqsave(&ctrl_info->raid_bypass_retry_list_lock, flags);
	if (at_head)
		list_add(&io_request->request_list_entry,
			&ctrl_info->raid_bypass_retry_list);
	else
		list_add_tail(&io_request->request_list_entry,
			&ctrl_info->raid_bypass_retry_list);
	spin_unlock_irqrestore(&ctrl_info->raid_bypass_retry_list_lock, flags);
}