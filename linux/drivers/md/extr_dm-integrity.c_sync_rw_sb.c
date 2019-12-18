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
struct TYPE_8__ {int /*<<< orphan*/ * fn; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {TYPE_1__ ptr; int /*<<< orphan*/  type; } ;
struct dm_io_request {int bi_op; int bi_op_flags; int /*<<< orphan*/  client; TYPE_3__ notify; TYPE_2__ mem; } ;
struct dm_io_region {int /*<<< orphan*/  count; int /*<<< orphan*/  sector; int /*<<< orphan*/  bdev; } ;
struct dm_integrity_c {int /*<<< orphan*/  start; TYPE_5__* dev; TYPE_4__* meta_dev; int /*<<< orphan*/  io; int /*<<< orphan*/  sb; } ;
struct TYPE_10__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_IO_KMEM ; 
 int REQ_OP_WRITE ; 
 int /*<<< orphan*/  SB_SECTORS ; 
 int dm_io (struct dm_io_request*,int,struct dm_io_region*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_set_version (struct dm_integrity_c*) ; 

__attribute__((used)) static int sync_rw_sb(struct dm_integrity_c *ic, int op, int op_flags)
{
	struct dm_io_request io_req;
	struct dm_io_region io_loc;

	io_req.bi_op = op;
	io_req.bi_op_flags = op_flags;
	io_req.mem.type = DM_IO_KMEM;
	io_req.mem.ptr.addr = ic->sb;
	io_req.notify.fn = NULL;
	io_req.client = ic->io;
	io_loc.bdev = ic->meta_dev ? ic->meta_dev->bdev : ic->dev->bdev;
	io_loc.sector = ic->start;
	io_loc.count = SB_SECTORS;

	if (op == REQ_OP_WRITE)
		sb_set_version(ic);

	return dm_io(&io_req, 1, &io_loc, NULL);
}