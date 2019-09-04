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
struct mirror {TYPE_4__* ms; } ;
struct TYPE_7__ {struct bio* context; int /*<<< orphan*/  fn; } ;
struct TYPE_5__ {struct bio* bio; } ;
struct TYPE_6__ {TYPE_1__ ptr; int /*<<< orphan*/  type; } ;
struct dm_io_request {int /*<<< orphan*/  client; TYPE_3__ notify; TYPE_2__ mem; int /*<<< orphan*/  bi_op_flags; int /*<<< orphan*/  bi_op; } ;
struct dm_io_region {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  io_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DM_IO_BIO ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  bio_set_m (struct bio*,struct mirror*) ; 
 int /*<<< orphan*/  dm_io (struct dm_io_request*,int,struct dm_io_region*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_region (struct dm_io_region*,struct mirror*,struct bio*) ; 
 int /*<<< orphan*/  read_callback ; 

__attribute__((used)) static void read_async_bio(struct mirror *m, struct bio *bio)
{
	struct dm_io_region io;
	struct dm_io_request io_req = {
		.bi_op = REQ_OP_READ,
		.bi_op_flags = 0,
		.mem.type = DM_IO_BIO,
		.mem.ptr.bio = bio,
		.notify.fn = read_callback,
		.notify.context = bio,
		.client = m->ms->io_client,
	};

	map_region(&io, m, bio);
	bio_set_m(bio, m);
	BUG_ON(dm_io(&io_req, 1, &io, NULL));
}