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
typedef  size_t u16 ;
struct hinic_cmdq {int /*<<< orphan*/  cmdq_lock; scalar_t__* done; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmdq_update_errcode (struct hinic_cmdq*,size_t,int) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void cmdq_sync_cmd_handler(struct hinic_cmdq *cmdq, u16 cons_idx,
				  int errcode)
{
	u16 prod_idx = cons_idx;

	spin_lock(&cmdq->cmdq_lock);
	cmdq_update_errcode(cmdq, prod_idx, errcode);

	wmb();  /* write all before update for the command request */

	if (cmdq->done[prod_idx])
		complete(cmdq->done[prod_idx]);
	spin_unlock(&cmdq->cmdq_lock);
}