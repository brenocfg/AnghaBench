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
struct request {int dummy; } ;
struct mapped_device {struct dm_target* immutable_target; } ;
struct dm_target {TYPE_1__* type; } ;
struct dm_table {int dummy; } ;
struct dm_rq_target_io {struct dm_target* ti; struct mapped_device* md; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {scalar_t__ (* busy ) (struct dm_target*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 scalar_t__ DM_MAPIO_REQUEUE ; 
 struct dm_rq_target_io* blk_mq_rq_to_pdu (struct request*) ; 
 struct dm_table* dm_get_live_table (struct mapped_device*,int*) ; 
 int /*<<< orphan*/  dm_put_live_table (struct mapped_device*,int) ; 
 int /*<<< orphan*/  dm_start_request (struct mapped_device*,struct request*) ; 
 struct dm_target* dm_table_find_target (struct dm_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_tio (struct dm_rq_target_io*,struct request*,struct mapped_device*) ; 
 scalar_t__ map_request (struct dm_rq_target_io*) ; 
 int /*<<< orphan*/  rq_completed (struct mapped_device*) ; 
 int /*<<< orphan*/  rq_end_stats (struct mapped_device*,struct request*) ; 
 scalar_t__ stub1 (struct dm_target*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static blk_status_t dm_mq_queue_rq(struct blk_mq_hw_ctx *hctx,
			  const struct blk_mq_queue_data *bd)
{
	struct request *rq = bd->rq;
	struct dm_rq_target_io *tio = blk_mq_rq_to_pdu(rq);
	struct mapped_device *md = tio->md;
	struct dm_target *ti = md->immutable_target;

	if (unlikely(!ti)) {
		int srcu_idx;
		struct dm_table *map = dm_get_live_table(md, &srcu_idx);

		ti = dm_table_find_target(map, 0);
		dm_put_live_table(md, srcu_idx);
	}

	if (ti->type->busy && ti->type->busy(ti))
		return BLK_STS_RESOURCE;

	dm_start_request(md, rq);

	/* Init tio using md established in .init_request */
	init_tio(tio, rq, md);

	/*
	 * Establish tio->ti before calling map_request().
	 */
	tio->ti = ti;

	/* Direct call is fine since .queue_rq allows allocations */
	if (map_request(tio) == DM_MAPIO_REQUEUE) {
		/* Undo dm_start_request() before requeuing */
		rq_end_stats(md, rq);
		rq_completed(md);
		return BLK_STS_RESOURCE;
	}

	return BLK_STS_OK;
}