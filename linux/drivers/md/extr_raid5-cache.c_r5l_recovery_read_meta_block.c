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
struct r5l_recovery_ctx {scalar_t__ pos; scalar_t__ seq; int /*<<< orphan*/  meta_total_blocks; struct page* meta_page; } ;
struct r5l_meta_block {scalar_t__ version; scalar_t__ meta_size; int /*<<< orphan*/  position; int /*<<< orphan*/  seq; scalar_t__ magic; scalar_t__ checksum; } ;
struct r5l_log {int /*<<< orphan*/  uuid_checksum; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SECTORS ; 
 int EINVAL ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ R5LOG_MAGIC ; 
 scalar_t__ R5LOG_VERSION ; 
 scalar_t__ crc32c_le (int /*<<< orphan*/ ,struct r5l_meta_block*,scalar_t__) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct r5l_meta_block* page_address (struct page*) ; 
 int r5l_recovery_read_page (struct r5l_log*,struct r5l_recovery_ctx*,struct page*,scalar_t__) ; 

__attribute__((used)) static int r5l_recovery_read_meta_block(struct r5l_log *log,
					struct r5l_recovery_ctx *ctx)
{
	struct page *page = ctx->meta_page;
	struct r5l_meta_block *mb;
	u32 crc, stored_crc;
	int ret;

	ret = r5l_recovery_read_page(log, ctx, page, ctx->pos);
	if (ret != 0)
		return ret;

	mb = page_address(page);
	stored_crc = le32_to_cpu(mb->checksum);
	mb->checksum = 0;

	if (le32_to_cpu(mb->magic) != R5LOG_MAGIC ||
	    le64_to_cpu(mb->seq) != ctx->seq ||
	    mb->version != R5LOG_VERSION ||
	    le64_to_cpu(mb->position) != ctx->pos)
		return -EINVAL;

	crc = crc32c_le(log->uuid_checksum, mb, PAGE_SIZE);
	if (stored_crc != crc)
		return -EINVAL;

	if (le32_to_cpu(mb->meta_size) > PAGE_SIZE)
		return -EINVAL;

	ctx->meta_total_blocks = BLOCK_SECTORS;

	return 0;
}