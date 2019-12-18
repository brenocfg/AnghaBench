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
struct scsi_cmnd {scalar_t__ retries; int /*<<< orphan*/  jiffies_at_alloc; int /*<<< orphan*/  rcu; int /*<<< orphan*/  req; } ;
struct request {int dummy; } ;

/* Variables and functions */
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  init_rcu_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  scsi_req_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scsi_initialize_rq(struct request *rq)
{
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(rq);

	scsi_req_init(&cmd->req);
	init_rcu_head(&cmd->rcu);
	cmd->jiffies_at_alloc = jiffies;
	cmd->retries = 0;
}