#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_4__ {TYPE_1__ ptr; int /*<<< orphan*/  type; } ;
struct dm_io_request {int bi_op_flags; int /*<<< orphan*/  client; TYPE_2__ mem; int /*<<< orphan*/  bi_op; } ;
struct dm_io_region {int /*<<< orphan*/  count; int /*<<< orphan*/  sector; int /*<<< orphan*/  bdev; } ;
struct dm_bufio_client {int /*<<< orphan*/  bdev; int /*<<< orphan*/  dm_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DM_IO_KMEM ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  dm_bufio_in_request () ; 
 int dm_io (struct dm_io_request*,int,struct dm_io_region*,int /*<<< orphan*/ *) ; 

int dm_bufio_issue_flush(struct dm_bufio_client *c)
{
	struct dm_io_request io_req = {
		.bi_op = REQ_OP_WRITE,
		.bi_op_flags = REQ_PREFLUSH | REQ_SYNC,
		.mem.type = DM_IO_KMEM,
		.mem.ptr.addr = NULL,
		.client = c->dm_io,
	};
	struct dm_io_region io_reg = {
		.bdev = c->bdev,
		.sector = 0,
		.count = 0,
	};

	BUG_ON(dm_bufio_in_request());

	return dm_io(&io_req, 1, &io_reg, NULL);
}