#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dm_writecache {int /*<<< orphan*/  dm_io; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fn; } ;
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_5__ {TYPE_1__ ptr; int /*<<< orphan*/  type; } ;
struct dm_io_request {TYPE_3__ notify; int /*<<< orphan*/  client; TYPE_2__ mem; int /*<<< orphan*/  bi_op_flags; int /*<<< orphan*/  bi_op; } ;
struct dm_io_region {scalar_t__ count; scalar_t__ sector; int /*<<< orphan*/  bdev; } ;
struct dm_dev {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_IO_KMEM ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  REQ_PREFLUSH ; 
 int dm_io (struct dm_io_request*,int,struct dm_io_region*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writecache_error (struct dm_writecache*,int,char*,int) ; 

__attribute__((used)) static void writecache_disk_flush(struct dm_writecache *wc, struct dm_dev *dev)
{
	int r;
	struct dm_io_region region;
	struct dm_io_request req;

	region.bdev = dev->bdev;
	region.sector = 0;
	region.count = 0;
	req.bi_op = REQ_OP_WRITE;
	req.bi_op_flags = REQ_PREFLUSH;
	req.mem.type = DM_IO_KMEM;
	req.mem.ptr.addr = NULL;
	req.client = wc->dm_io;
	req.notify.fn = NULL;

	r = dm_io(&req, 1, &region, NULL);
	if (unlikely(r))
		writecache_error(wc, r, "error flushing metadata: %d", r);
}