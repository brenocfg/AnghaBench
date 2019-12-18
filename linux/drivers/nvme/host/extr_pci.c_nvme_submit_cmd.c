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
struct nvme_queue {int sq_tail; int sqes; int q_depth; int /*<<< orphan*/  sq_lock; scalar_t__ sq_cmds; } ;
struct nvme_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,struct nvme_command*,int) ; 
 int /*<<< orphan*/  nvme_write_sq_db (struct nvme_queue*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_submit_cmd(struct nvme_queue *nvmeq, struct nvme_command *cmd,
			    bool write_sq)
{
	spin_lock(&nvmeq->sq_lock);
	memcpy(nvmeq->sq_cmds + (nvmeq->sq_tail << nvmeq->sqes),
	       cmd, sizeof(*cmd));
	if (++nvmeq->sq_tail == nvmeq->q_depth)
		nvmeq->sq_tail = 0;
	nvme_write_sq_db(nvmeq, write_sq);
	spin_unlock(&nvmeq->sq_lock);
}