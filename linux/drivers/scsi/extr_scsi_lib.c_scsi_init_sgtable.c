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
struct TYPE_2__ {int nents; int /*<<< orphan*/  sgl; } ;
struct scsi_data_buffer {int /*<<< orphan*/  length; TYPE_1__ table; } ;
struct request {int /*<<< orphan*/  q; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SCSI_INLINE_SG_CNT ; 
 int blk_rq_map_sg (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_nr_phys_segments (struct request*) ; 
 int /*<<< orphan*/  blk_rq_payload_bytes (struct request*) ; 
 int /*<<< orphan*/  sg_alloc_table_chained (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t scsi_init_sgtable(struct request *req,
		struct scsi_data_buffer *sdb)
{
	int count;

	/*
	 * If sg table allocation fails, requeue request later.
	 */
	if (unlikely(sg_alloc_table_chained(&sdb->table,
			blk_rq_nr_phys_segments(req), sdb->table.sgl,
			SCSI_INLINE_SG_CNT)))
		return BLK_STS_RESOURCE;

	/* 
	 * Next, walk the list, and fill in the addresses and sizes of
	 * each segment.
	 */
	count = blk_rq_map_sg(req->q, req, sdb->table.sgl);
	BUG_ON(count > sdb->table.nents);
	sdb->table.nents = count;
	sdb->length = blk_rq_payload_bytes(req);
	return BLK_STS_OK;
}