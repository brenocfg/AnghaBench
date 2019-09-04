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
typedef  int u64 ;
struct ccp_cmd_queue {int id; TYPE_1__* ccp; int /*<<< orphan*/  lsbmask; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int LSB_REGION_WIDTH ; 
 int MAX_LSB_CNT ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int bitmap_weight (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int ccp_find_lsb_regions(struct ccp_cmd_queue *cmd_q, u64 status)
{
	int q_mask = 1 << cmd_q->id;
	int queues = 0;
	int j;

	/* Build a bit mask to know which LSBs this queue has access to.
	 * Don't bother with segment 0 as it has special privileges.
	 */
	for (j = 1; j < MAX_LSB_CNT; j++) {
		if (status & q_mask)
			bitmap_set(cmd_q->lsbmask, j, 1);
		status >>= LSB_REGION_WIDTH;
	}
	queues = bitmap_weight(cmd_q->lsbmask, MAX_LSB_CNT);
	dev_dbg(cmd_q->ccp->dev, "Queue %d can access %d LSB regions\n",
		 cmd_q->id, queues);

	return queues ? 0 : -EINVAL;
}