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
typedef  int /*<<< orphan*/  u64 ;
struct r5l_meta_block {int /*<<< orphan*/  checksum; } ;
struct r5l_log {int /*<<< orphan*/  rdev; int /*<<< orphan*/  uuid_checksum; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int REQ_FUA ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32c_le (int /*<<< orphan*/ ,struct r5l_meta_block*,int /*<<< orphan*/ ) ; 
 struct r5l_meta_block* page_address (struct page*) ; 
 int /*<<< orphan*/  r5l_recovery_create_empty_meta_block (struct r5l_log*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_page_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int r5l_log_write_empty_meta_block(struct r5l_log *log, sector_t pos,
					  u64 seq)
{
	struct page *page;
	struct r5l_meta_block *mb;

	page = alloc_page(GFP_KERNEL);
	if (!page)
		return -ENOMEM;
	r5l_recovery_create_empty_meta_block(log, page, pos, seq);
	mb = page_address(page);
	mb->checksum = cpu_to_le32(crc32c_le(log->uuid_checksum,
					     mb, PAGE_SIZE));
	if (!sync_page_io(log->rdev, pos, PAGE_SIZE, page, REQ_OP_WRITE,
			  REQ_SYNC | REQ_FUA, false)) {
		__free_page(page);
		return -EIO;
	}
	__free_page(page);
	return 0;
}