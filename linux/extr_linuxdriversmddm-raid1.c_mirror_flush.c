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
struct mirror_set {unsigned int nr_mirrors; struct mirror* mirror; int /*<<< orphan*/  io_client; } ;
struct mirror {TYPE_3__* dev; } ;
struct dm_target {struct mirror_set* private; } ;
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_5__ {TYPE_1__ ptr; int /*<<< orphan*/  type; } ;
struct dm_io_request {int bi_op_flags; int /*<<< orphan*/  client; TYPE_2__ mem; int /*<<< orphan*/  bi_op; } ;
struct dm_io_region {scalar_t__ count; scalar_t__ sector; int /*<<< orphan*/  bdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_IO_KMEM ; 
 int /*<<< orphan*/  DM_RAID1_FLUSH_ERROR ; 
 int EIO ; 
 int MAX_NR_MIRRORS ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  dm_io (struct dm_io_request*,unsigned int,struct dm_io_region*,unsigned long*) ; 
 int /*<<< orphan*/  fail_mirror (struct mirror*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned int,unsigned long*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mirror_flush(struct dm_target *ti)
{
	struct mirror_set *ms = ti->private;
	unsigned long error_bits;

	unsigned int i;
	struct dm_io_region io[MAX_NR_MIRRORS];
	struct mirror *m;
	struct dm_io_request io_req = {
		.bi_op = REQ_OP_WRITE,
		.bi_op_flags = REQ_PREFLUSH | REQ_SYNC,
		.mem.type = DM_IO_KMEM,
		.mem.ptr.addr = NULL,
		.client = ms->io_client,
	};

	for (i = 0, m = ms->mirror; i < ms->nr_mirrors; i++, m++) {
		io[i].bdev = m->dev->bdev;
		io[i].sector = 0;
		io[i].count = 0;
	}

	error_bits = -1;
	dm_io(&io_req, ms->nr_mirrors, io, &error_bits);
	if (unlikely(error_bits != 0)) {
		for (i = 0; i < ms->nr_mirrors; i++)
			if (test_bit(i, &error_bits))
				fail_mirror(ms->mirror + i,
					    DM_RAID1_FLUSH_ERROR);
		return -EIO;
	}

	return 0;
}