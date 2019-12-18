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
struct nvme_loop_iod {int /*<<< orphan*/  sg_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  SG_CHUNK_SIZE ; 
 struct nvme_loop_iod* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  nvme_cleanup_cmd (struct request*) ; 
 int /*<<< orphan*/  nvme_complete_rq (struct request*) ; 
 int /*<<< orphan*/  sg_free_table_chained (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_loop_complete_rq(struct request *req)
{
	struct nvme_loop_iod *iod = blk_mq_rq_to_pdu(req);

	nvme_cleanup_cmd(req);
	sg_free_table_chained(&iod->sg_table, SG_CHUNK_SIZE);
	nvme_complete_rq(req);
}