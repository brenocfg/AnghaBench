#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* context; int /*<<< orphan*/  (* fn ) (unsigned long,void*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * pl; } ;
struct TYPE_6__ {unsigned int offset; TYPE_1__ ptr; int /*<<< orphan*/  type; } ;
struct dm_io_request {int /*<<< orphan*/  client; TYPE_3__ notify; TYPE_2__ mem; scalar_t__ bi_op_flags; int /*<<< orphan*/  bi_op; } ;
struct dm_io_region {unsigned int sector; unsigned int count; int /*<<< orphan*/  bdev; } ;
struct dm_integrity_c {int sectors_per_block; unsigned int journal_section_sectors; TYPE_4__* dev; int /*<<< orphan*/  io; int /*<<< orphan*/ * journal; } ;
typedef  unsigned int sector_t ;
typedef  int /*<<< orphan*/  (* io_notify_fn ) (unsigned long,void*) ;
struct TYPE_8__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned int) ; 
 int /*<<< orphan*/  DM_IO_PAGE_LIST ; 
 unsigned int JOURNAL_BLOCK_SECTORS ; 
 unsigned int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 unsigned int SECTOR_SHIFT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int dm_integrity_failed (struct dm_integrity_c*) ; 
 int dm_io (struct dm_io_request*,int,struct dm_io_region*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void copy_from_journal(struct dm_integrity_c *ic, unsigned section, unsigned offset,
			      unsigned n_sectors, sector_t target, io_notify_fn fn, void *data)
{
	struct dm_io_request io_req;
	struct dm_io_region io_loc;
	int r;
	unsigned sector, pl_index, pl_offset;

	BUG_ON((target | n_sectors | offset) & (unsigned)(ic->sectors_per_block - 1));

	if (unlikely(dm_integrity_failed(ic))) {
		fn(-1UL, data);
		return;
	}

	sector = section * ic->journal_section_sectors + JOURNAL_BLOCK_SECTORS + offset;

	pl_index = sector >> (PAGE_SHIFT - SECTOR_SHIFT);
	pl_offset = (sector << SECTOR_SHIFT) & (PAGE_SIZE - 1);

	io_req.bi_op = REQ_OP_WRITE;
	io_req.bi_op_flags = 0;
	io_req.mem.type = DM_IO_PAGE_LIST;
	io_req.mem.ptr.pl = &ic->journal[pl_index];
	io_req.mem.offset = pl_offset;
	io_req.notify.fn = fn;
	io_req.notify.context = data;
	io_req.client = ic->io;
	io_loc.bdev = ic->dev->bdev;
	io_loc.sector = target;
	io_loc.count = n_sectors;

	r = dm_io(&io_req, 1, &io_loc, NULL);
	if (unlikely(r)) {
		WARN_ONCE(1, "asynchronous dm_io failed: %d", r);
		fn(-1UL, data);
	}
}