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
struct pqi_queue_group {int /*<<< orphan*/ * submit_lock; int /*<<< orphan*/ * request_list; } ;
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqi_check_ctrl_health (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_ctrl_offline (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pqi_wait_until_queued_io_drained(struct pqi_ctrl_info *ctrl_info,
	struct pqi_queue_group *queue_group)
{
	unsigned int path;
	unsigned long flags;
	bool list_is_empty;

	for (path = 0; path < 2; path++) {
		while (1) {
			spin_lock_irqsave(
				&queue_group->submit_lock[path], flags);
			list_is_empty =
				list_empty(&queue_group->request_list[path]);
			spin_unlock_irqrestore(
				&queue_group->submit_lock[path], flags);
			if (list_is_empty)
				break;
			pqi_check_ctrl_health(ctrl_info);
			if (pqi_ctrl_offline(ctrl_info))
				return -ENXIO;
			usleep_range(1000, 2000);
		}
	}

	return 0;
}