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
struct mapped_device {scalar_t__ init_tio_pdu; } ;
struct TYPE_2__ {struct dm_rq_target_io* ptr; } ;
struct dm_rq_target_io {TYPE_1__ info; struct mapped_device* md; } ;
struct blk_mq_tag_set {struct mapped_device* driver_data; } ;

/* Variables and functions */
 struct dm_rq_target_io* blk_mq_rq_to_pdu (struct request*) ; 

__attribute__((used)) static int dm_mq_init_request(struct blk_mq_tag_set *set, struct request *rq,
			      unsigned int hctx_idx, unsigned int numa_node)
{
	struct mapped_device *md = set->driver_data;
	struct dm_rq_target_io *tio = blk_mq_rq_to_pdu(rq);

	/*
	 * Must initialize md member of tio, otherwise it won't
	 * be available in dm_mq_queue_rq.
	 */
	tio->md = md;

	if (md->init_tio_pdu) {
		/* target-specific per-io data is immediately after the tio */
		tio->info.ptr = tio + 1;
	}

	return 0;
}