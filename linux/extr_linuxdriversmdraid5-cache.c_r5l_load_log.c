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
typedef  scalar_t__ u32 ;
struct r5l_meta_block {scalar_t__ version; int /*<<< orphan*/  seq; int /*<<< orphan*/  position; scalar_t__ checksum; scalar_t__ magic; } ;
struct r5l_log {int device_size; int max_free_space; scalar_t__ next_checkpoint; scalar_t__ last_cp_seq; scalar_t__ seq; int /*<<< orphan*/  log_start; scalar_t__ last_checkpoint; int /*<<< orphan*/  uuid_checksum; struct md_rdev* rdev; } ;
struct page {int dummy; } ;
struct md_rdev {scalar_t__ journal_tail; scalar_t__ sectors; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SECTORS ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ R5LOG_MAGIC ; 
 scalar_t__ R5LOG_VERSION ; 
 int RECLAIM_MAX_FREE_SPACE ; 
 int RECLAIM_MAX_FREE_SPACE_SHIFT ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 scalar_t__ crc32c_le (int /*<<< orphan*/ ,struct r5l_meta_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct r5l_meta_block* page_address (struct page*) ; 
 scalar_t__ prandom_u32 () ; 
 int /*<<< orphan*/  r5c_update_log_state (struct r5l_log*) ; 
 int /*<<< orphan*/  r5l_log_write_empty_meta_block (struct r5l_log*,scalar_t__,scalar_t__) ; 
 int r5l_recovery_log (struct r5l_log*) ; 
 int /*<<< orphan*/  r5l_ring_add (struct r5l_log*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5l_write_super (struct r5l_log*,scalar_t__) ; 
 scalar_t__ round_down (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_page_io (struct md_rdev*,scalar_t__,int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r5l_load_log(struct r5l_log *log)
{
	struct md_rdev *rdev = log->rdev;
	struct page *page;
	struct r5l_meta_block *mb;
	sector_t cp = log->rdev->journal_tail;
	u32 stored_crc, expected_crc;
	bool create_super = false;
	int ret = 0;

	/* Make sure it's valid */
	if (cp >= rdev->sectors || round_down(cp, BLOCK_SECTORS) != cp)
		cp = 0;
	page = alloc_page(GFP_KERNEL);
	if (!page)
		return -ENOMEM;

	if (!sync_page_io(rdev, cp, PAGE_SIZE, page, REQ_OP_READ, 0, false)) {
		ret = -EIO;
		goto ioerr;
	}
	mb = page_address(page);

	if (le32_to_cpu(mb->magic) != R5LOG_MAGIC ||
	    mb->version != R5LOG_VERSION) {
		create_super = true;
		goto create;
	}
	stored_crc = le32_to_cpu(mb->checksum);
	mb->checksum = 0;
	expected_crc = crc32c_le(log->uuid_checksum, mb, PAGE_SIZE);
	if (stored_crc != expected_crc) {
		create_super = true;
		goto create;
	}
	if (le64_to_cpu(mb->position) != cp) {
		create_super = true;
		goto create;
	}
create:
	if (create_super) {
		log->last_cp_seq = prandom_u32();
		cp = 0;
		r5l_log_write_empty_meta_block(log, cp, log->last_cp_seq);
		/*
		 * Make sure super points to correct address. Log might have
		 * data very soon. If super hasn't correct log tail address,
		 * recovery can't find the log
		 */
		r5l_write_super(log, cp);
	} else
		log->last_cp_seq = le64_to_cpu(mb->seq);

	log->device_size = round_down(rdev->sectors, BLOCK_SECTORS);
	log->max_free_space = log->device_size >> RECLAIM_MAX_FREE_SPACE_SHIFT;
	if (log->max_free_space > RECLAIM_MAX_FREE_SPACE)
		log->max_free_space = RECLAIM_MAX_FREE_SPACE;
	log->last_checkpoint = cp;

	__free_page(page);

	if (create_super) {
		log->log_start = r5l_ring_add(log, cp, BLOCK_SECTORS);
		log->seq = log->last_cp_seq + 1;
		log->next_checkpoint = cp;
	} else
		ret = r5l_recovery_log(log);

	r5c_update_log_state(log);
	return ret;
ioerr:
	__free_page(page);
	return ret;
}