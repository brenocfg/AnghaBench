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
struct queue_limits {int dummy; } ;
struct mapped_device {int /*<<< orphan*/  disk; int /*<<< orphan*/  queue; } ;
struct dm_table {int dummy; } ;
typedef  enum dm_queue_mode { ____Placeholder_dm_queue_mode } dm_queue_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
#define  DM_TYPE_BIO_BASED 132 
#define  DM_TYPE_DAX_BIO_BASED 131 
#define  DM_TYPE_NONE 130 
#define  DM_TYPE_NVME_BIO_BASED 129 
#define  DM_TYPE_REQUEST_BASED 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_queue_make_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_register_queue (int /*<<< orphan*/ ) ; 
 int dm_calculate_queue_limits (struct dm_table*,struct queue_limits*) ; 
 int dm_get_md_type (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_init_normal_md_queue (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_make_request ; 
 int dm_mq_init_request_queue (struct mapped_device*,struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_set_restrictions (struct dm_table*,int /*<<< orphan*/ ,struct queue_limits*) ; 

int dm_setup_md_queue(struct mapped_device *md, struct dm_table *t)
{
	int r;
	struct queue_limits limits;
	enum dm_queue_mode type = dm_get_md_type(md);

	switch (type) {
	case DM_TYPE_REQUEST_BASED:
		r = dm_mq_init_request_queue(md, t);
		if (r) {
			DMERR("Cannot initialize queue for request-based dm-mq mapped device");
			return r;
		}
		break;
	case DM_TYPE_BIO_BASED:
	case DM_TYPE_DAX_BIO_BASED:
	case DM_TYPE_NVME_BIO_BASED:
		dm_init_normal_md_queue(md);
		blk_queue_make_request(md->queue, dm_make_request);
		break;
	case DM_TYPE_NONE:
		WARN_ON_ONCE(true);
		break;
	}

	r = dm_calculate_queue_limits(t, &limits);
	if (r) {
		DMERR("Cannot calculate initial queue limits");
		return r;
	}
	dm_table_set_restrictions(t, md->queue, &limits);
	blk_register_queue(md->disk);

	return 0;
}