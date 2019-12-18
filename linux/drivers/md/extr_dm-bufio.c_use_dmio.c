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
struct TYPE_7__ {char* addr; char* vma; } ;
struct TYPE_8__ {TYPE_3__ ptr; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {struct dm_buffer* context; int /*<<< orphan*/  fn; } ;
struct dm_io_request {int bi_op; TYPE_4__ mem; int /*<<< orphan*/  client; TYPE_1__ notify; int /*<<< orphan*/  bi_op_flags; } ;
struct dm_io_region {unsigned int count; int /*<<< orphan*/  sector; int /*<<< orphan*/  bdev; } ;
struct dm_buffer {scalar_t__ data_mode; int /*<<< orphan*/  (* end_io ) (struct dm_buffer*,int /*<<< orphan*/ ) ;scalar_t__ data; TYPE_2__* c; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; int /*<<< orphan*/  dm_io; } ;

/* Variables and functions */
 scalar_t__ DATA_MODE_VMALLOC ; 
 int /*<<< orphan*/  DM_IO_KMEM ; 
 int /*<<< orphan*/  DM_IO_VMA ; 
 int dm_io (struct dm_io_request*,int,struct dm_io_region*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmio_complete ; 
 int /*<<< orphan*/  errno_to_blk_status (int) ; 
 int /*<<< orphan*/  stub1 (struct dm_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void use_dmio(struct dm_buffer *b, int rw, sector_t sector,
		     unsigned n_sectors, unsigned offset)
{
	int r;
	struct dm_io_request io_req = {
		.bi_op = rw,
		.bi_op_flags = 0,
		.notify.fn = dmio_complete,
		.notify.context = b,
		.client = b->c->dm_io,
	};
	struct dm_io_region region = {
		.bdev = b->c->bdev,
		.sector = sector,
		.count = n_sectors,
	};

	if (b->data_mode != DATA_MODE_VMALLOC) {
		io_req.mem.type = DM_IO_KMEM;
		io_req.mem.ptr.addr = (char *)b->data + offset;
	} else {
		io_req.mem.type = DM_IO_VMA;
		io_req.mem.ptr.vma = (char *)b->data + offset;
	}

	r = dm_io(&io_req, 1, &region, NULL);
	if (unlikely(r))
		b->end_io(b, errno_to_blk_status(r));
}