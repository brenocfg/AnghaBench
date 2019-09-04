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
struct request {int dummy; } ;
struct nbd_cmd {int /*<<< orphan*/  lock; scalar_t__ flags; int /*<<< orphan*/  nbd; } ;
struct blk_mq_tag_set {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 struct nbd_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nbd_init_request(struct blk_mq_tag_set *set, struct request *rq,
			    unsigned int hctx_idx, unsigned int numa_node)
{
	struct nbd_cmd *cmd = blk_mq_rq_to_pdu(rq);
	cmd->nbd = set->driver_data;
	cmd->flags = 0;
	mutex_init(&cmd->lock);
	return 0;
}