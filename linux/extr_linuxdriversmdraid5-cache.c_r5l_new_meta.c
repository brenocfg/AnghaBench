#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r5l_meta_block {void* position; void* seq; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
struct r5l_log {int /*<<< orphan*/  io_list_lock; int /*<<< orphan*/  running_ios; int /*<<< orphan*/  seq; int /*<<< orphan*/  log_start; int /*<<< orphan*/  meta_pool; int /*<<< orphan*/  io_pool; } ;
struct r5l_io_unit {int meta_offset; int /*<<< orphan*/  log_sibling; void* meta_page; TYPE_1__* current_bio; scalar_t__ seq; int /*<<< orphan*/  log_start; int /*<<< orphan*/  state; int /*<<< orphan*/  flush_barriers; int /*<<< orphan*/  stripe_list; struct r5l_log* log; } ;
struct TYPE_3__ {struct r5l_io_unit* bi_private; int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IO_UNIT_RUNNING ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  R5LOG_MAGIC ; 
 int /*<<< orphan*/  R5LOG_VERSION ; 
 int /*<<< orphan*/  bio_add_page (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_page (struct r5l_meta_block*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct r5l_io_unit*,int /*<<< orphan*/ ,int) ; 
 struct r5l_meta_block* page_address (void*) ; 
 int /*<<< orphan*/  r5_reserve_log_entry (struct r5l_log*,struct r5l_io_unit*) ; 
 TYPE_1__* r5l_bio_alloc (struct r5l_log*) ; 
 int /*<<< orphan*/  r5l_log_endio ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct r5l_io_unit *r5l_new_meta(struct r5l_log *log)
{
	struct r5l_io_unit *io;
	struct r5l_meta_block *block;

	io = mempool_alloc(&log->io_pool, GFP_ATOMIC);
	if (!io)
		return NULL;
	memset(io, 0, sizeof(*io));

	io->log = log;
	INIT_LIST_HEAD(&io->log_sibling);
	INIT_LIST_HEAD(&io->stripe_list);
	bio_list_init(&io->flush_barriers);
	io->state = IO_UNIT_RUNNING;

	io->meta_page = mempool_alloc(&log->meta_pool, GFP_NOIO);
	block = page_address(io->meta_page);
	clear_page(block);
	block->magic = cpu_to_le32(R5LOG_MAGIC);
	block->version = R5LOG_VERSION;
	block->seq = cpu_to_le64(log->seq);
	block->position = cpu_to_le64(log->log_start);

	io->log_start = log->log_start;
	io->meta_offset = sizeof(struct r5l_meta_block);
	io->seq = log->seq++;

	io->current_bio = r5l_bio_alloc(log);
	io->current_bio->bi_end_io = r5l_log_endio;
	io->current_bio->bi_private = io;
	bio_add_page(io->current_bio, io->meta_page, PAGE_SIZE, 0);

	r5_reserve_log_entry(log, io);

	spin_lock_irq(&log->io_list_lock);
	list_add_tail(&io->log_sibling, &log->running_ios);
	spin_unlock_irq(&log->io_list_lock);

	return io;
}