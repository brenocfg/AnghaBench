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
struct verify_rq_based_data {scalar_t__ sq_count; int /*<<< orphan*/  mq_count; } ;
struct list_head {int dummy; } ;
struct dm_target {TYPE_1__* type; scalar_t__ max_io_len; } ;
struct dm_table {scalar_t__ type; unsigned int num_targets; int /*<<< orphan*/  md; struct dm_target* targets; } ;
typedef  enum dm_queue_mode { ____Placeholder_dm_queue_mode } dm_queue_mode ;
struct TYPE_2__ {int /*<<< orphan*/  (* iterate_devices ) (struct dm_target*,int /*<<< orphan*/ ,struct verify_rq_based_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMERR (char*,...) ; 
 scalar_t__ DM_TYPE_BIO_BASED ; 
 scalar_t__ DM_TYPE_DAX_BIO_BASED ; 
 scalar_t__ DM_TYPE_NONE ; 
 scalar_t__ DM_TYPE_NVME_BIO_BASED ; 
 scalar_t__ DM_TYPE_REQUEST_BASED ; 
 int EINVAL ; 
 int PAGE_SIZE ; 
 scalar_t__ __table_type_request_based (int) ; 
 int /*<<< orphan*/  device_is_rq_based ; 
 int /*<<< orphan*/  device_supports_dax ; 
 struct dm_table* dm_get_live_table (int /*<<< orphan*/ ,int*) ; 
 int dm_get_md_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_put_live_table (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dm_table_does_not_support_partial_completion (struct dm_table*) ; 
 struct list_head* dm_table_get_devices (struct dm_table*) ; 
 struct dm_target* dm_table_get_immutable_target (struct dm_table*) ; 
 scalar_t__ dm_table_supports_dax (struct dm_table*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ dm_target_hybrid (struct dm_target*) ; 
 scalar_t__ dm_target_request_based (struct dm_target*) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  stub1 (struct dm_target*,int /*<<< orphan*/ ,struct verify_rq_based_data*) ; 

__attribute__((used)) static int dm_table_determine_type(struct dm_table *t)
{
	unsigned i;
	unsigned bio_based = 0, request_based = 0, hybrid = 0;
	struct verify_rq_based_data v = {.sq_count = 0, .mq_count = 0};
	struct dm_target *tgt;
	struct list_head *devices = dm_table_get_devices(t);
	enum dm_queue_mode live_md_type = dm_get_md_type(t->md);
	int page_size = PAGE_SIZE;

	if (t->type != DM_TYPE_NONE) {
		/* target already set the table's type */
		if (t->type == DM_TYPE_BIO_BASED) {
			/* possibly upgrade to a variant of bio-based */
			goto verify_bio_based;
		}
		BUG_ON(t->type == DM_TYPE_DAX_BIO_BASED);
		BUG_ON(t->type == DM_TYPE_NVME_BIO_BASED);
		goto verify_rq_based;
	}

	for (i = 0; i < t->num_targets; i++) {
		tgt = t->targets + i;
		if (dm_target_hybrid(tgt))
			hybrid = 1;
		else if (dm_target_request_based(tgt))
			request_based = 1;
		else
			bio_based = 1;

		if (bio_based && request_based) {
			DMERR("Inconsistent table: different target types"
			      " can't be mixed up");
			return -EINVAL;
		}
	}

	if (hybrid && !bio_based && !request_based) {
		/*
		 * The targets can work either way.
		 * Determine the type from the live device.
		 * Default to bio-based if device is new.
		 */
		if (__table_type_request_based(live_md_type))
			request_based = 1;
		else
			bio_based = 1;
	}

	if (bio_based) {
verify_bio_based:
		/* We must use this table as bio-based */
		t->type = DM_TYPE_BIO_BASED;
		if (dm_table_supports_dax(t, device_supports_dax, &page_size) ||
		    (list_empty(devices) && live_md_type == DM_TYPE_DAX_BIO_BASED)) {
			t->type = DM_TYPE_DAX_BIO_BASED;
		} else {
			/* Check if upgrading to NVMe bio-based is valid or required */
			tgt = dm_table_get_immutable_target(t);
			if (tgt && !tgt->max_io_len && dm_table_does_not_support_partial_completion(t)) {
				t->type = DM_TYPE_NVME_BIO_BASED;
				goto verify_rq_based; /* must be stacked directly on NVMe (blk-mq) */
			} else if (list_empty(devices) && live_md_type == DM_TYPE_NVME_BIO_BASED) {
				t->type = DM_TYPE_NVME_BIO_BASED;
			}
		}
		return 0;
	}

	BUG_ON(!request_based); /* No targets in this table */

	t->type = DM_TYPE_REQUEST_BASED;

verify_rq_based:
	/*
	 * Request-based dm supports only tables that have a single target now.
	 * To support multiple targets, request splitting support is needed,
	 * and that needs lots of changes in the block-layer.
	 * (e.g. request completion process for partial completion.)
	 */
	if (t->num_targets > 1) {
		DMERR("%s DM doesn't support multiple targets",
		      t->type == DM_TYPE_NVME_BIO_BASED ? "nvme bio-based" : "request-based");
		return -EINVAL;
	}

	if (list_empty(devices)) {
		int srcu_idx;
		struct dm_table *live_table = dm_get_live_table(t->md, &srcu_idx);

		/* inherit live table's type */
		if (live_table)
			t->type = live_table->type;
		dm_put_live_table(t->md, srcu_idx);
		return 0;
	}

	tgt = dm_table_get_immutable_target(t);
	if (!tgt) {
		DMERR("table load rejected: immutable target is required");
		return -EINVAL;
	} else if (tgt->max_io_len) {
		DMERR("table load rejected: immutable target that splits IO is not supported");
		return -EINVAL;
	}

	/* Non-request-stackable devices can't be used for request-based dm */
	if (!tgt->type->iterate_devices ||
	    !tgt->type->iterate_devices(tgt, device_is_rq_based, &v)) {
		DMERR("table load rejected: including non-request-stackable devices");
		return -EINVAL;
	}
	if (v.sq_count > 0) {
		DMERR("table load rejected: not all devices are blk-mq request-stackable");
		return -EINVAL;
	}

	return 0;
}