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
struct io {int /*<<< orphan*/  vma_invalidate_size; int /*<<< orphan*/  vma_invalidate_address; void* context; int /*<<< orphan*/  (* callback ) (int,void*) ;struct dm_io_client* client; int /*<<< orphan*/  count; scalar_t__ error_bits; } ;
struct dpages {int /*<<< orphan*/  vma_invalidate_size; int /*<<< orphan*/  vma_invalidate_address; } ;
struct dm_io_region {int dummy; } ;
struct dm_io_client {int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  (* io_notify_fn ) (int,void*) ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dispatch_io (int,int,unsigned int,struct dm_io_region*,struct dpages*,struct io*,int /*<<< orphan*/ ) ; 
 struct io* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_is_write (int) ; 

__attribute__((used)) static int async_io(struct dm_io_client *client, unsigned int num_regions,
		    struct dm_io_region *where, int op, int op_flags,
		    struct dpages *dp, io_notify_fn fn, void *context)
{
	struct io *io;

	if (num_regions > 1 && !op_is_write(op)) {
		WARN_ON(1);
		fn(1, context);
		return -EIO;
	}

	io = mempool_alloc(&client->pool, GFP_NOIO);
	io->error_bits = 0;
	atomic_set(&io->count, 1); /* see dispatch_io() */
	io->client = client;
	io->callback = fn;
	io->context = context;

	io->vma_invalidate_address = dp->vma_invalidate_address;
	io->vma_invalidate_size = dp->vma_invalidate_size;

	dispatch_io(op, op_flags, num_regions, where, dp, io, 0);
	return 0;
}