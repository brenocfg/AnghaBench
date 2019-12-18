#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct journal_completion {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* fn ) (unsigned long,struct journal_completion*) ;struct journal_completion* context; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pl; } ;
struct TYPE_7__ {unsigned int offset; TYPE_1__ ptr; int /*<<< orphan*/  type; } ;
struct dm_io_request {int bi_op; int bi_op_flags; int /*<<< orphan*/  client; TYPE_3__ notify; TYPE_2__ mem; } ;
struct dm_io_region {unsigned int count; scalar_t__ sector; int /*<<< orphan*/  bdev; } ;
struct dm_integrity_c {scalar_t__ start; TYPE_5__* dev; TYPE_4__* meta_dev; int /*<<< orphan*/  io; int /*<<< orphan*/ * journal; int /*<<< orphan*/ * journal_io; } ;
struct TYPE_10__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_IO_PAGE_LIST ; 
 unsigned int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int REQ_OP_READ ; 
 scalar_t__ SB_SECTORS ; 
 unsigned int SECTOR_SHIFT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  complete_journal_io (unsigned long,struct journal_completion*) ; 
 int dm_integrity_failed (struct dm_integrity_c*) ; 
 int /*<<< orphan*/  dm_integrity_io_error (struct dm_integrity_c*,char*,int) ; 
 int dm_io (struct dm_io_request*,int,struct dm_io_region*,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rw_journal_sectors(struct dm_integrity_c *ic, int op, int op_flags,
			       unsigned sector, unsigned n_sectors, struct journal_completion *comp)
{
	struct dm_io_request io_req;
	struct dm_io_region io_loc;
	unsigned pl_index, pl_offset;
	int r;

	if (unlikely(dm_integrity_failed(ic))) {
		if (comp)
			complete_journal_io(-1UL, comp);
		return;
	}

	pl_index = sector >> (PAGE_SHIFT - SECTOR_SHIFT);
	pl_offset = (sector << SECTOR_SHIFT) & (PAGE_SIZE - 1);

	io_req.bi_op = op;
	io_req.bi_op_flags = op_flags;
	io_req.mem.type = DM_IO_PAGE_LIST;
	if (ic->journal_io)
		io_req.mem.ptr.pl = &ic->journal_io[pl_index];
	else
		io_req.mem.ptr.pl = &ic->journal[pl_index];
	io_req.mem.offset = pl_offset;
	if (likely(comp != NULL)) {
		io_req.notify.fn = complete_journal_io;
		io_req.notify.context = comp;
	} else {
		io_req.notify.fn = NULL;
	}
	io_req.client = ic->io;
	io_loc.bdev = ic->meta_dev ? ic->meta_dev->bdev : ic->dev->bdev;
	io_loc.sector = ic->start + SB_SECTORS + sector;
	io_loc.count = n_sectors;

	r = dm_io(&io_req, 1, &io_loc, NULL);
	if (unlikely(r)) {
		dm_integrity_io_error(ic, op == REQ_OP_READ ? "reading journal" : "writing journal", r);
		if (comp) {
			WARN_ONCE(1, "asynchronous dm_io failed: %d", r);
			complete_journal_io(-1UL, comp);
		}
	}
}