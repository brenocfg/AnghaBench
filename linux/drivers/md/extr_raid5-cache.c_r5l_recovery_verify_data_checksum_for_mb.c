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
struct r5l_recovery_ctx {int pos; int /*<<< orphan*/  meta_page; } ;
struct r5l_payload_flush {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct r5l_payload_data_parity {int /*<<< orphan*/  size; TYPE_2__ header; int /*<<< orphan*/ * checksum; } ;
struct r5l_meta_block {int /*<<< orphan*/  meta_size; } ;
struct r5l_log {TYPE_1__* rdev; } ;
struct r5conf {int max_degraded; } ;
struct page {int dummy; } ;
struct mddev {struct r5conf* private; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {struct mddev* mddev; } ;

/* Variables and functions */
 int BLOCK_SECTORS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 scalar_t__ R5LOG_PAYLOAD_DATA ; 
 scalar_t__ R5LOG_PAYLOAD_FLUSH ; 
 scalar_t__ R5LOG_PAYLOAD_PARITY ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct r5l_meta_block* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ r5l_recovery_verify_data_checksum (struct r5l_log*,struct r5l_recovery_ctx*,struct page*,int,int /*<<< orphan*/ ) ; 
 int r5l_ring_add (struct r5l_log*,int,int) ; 

__attribute__((used)) static int
r5l_recovery_verify_data_checksum_for_mb(struct r5l_log *log,
					 struct r5l_recovery_ctx *ctx)
{
	struct mddev *mddev = log->rdev->mddev;
	struct r5conf *conf = mddev->private;
	struct r5l_meta_block *mb = page_address(ctx->meta_page);
	sector_t mb_offset = sizeof(struct r5l_meta_block);
	sector_t log_offset = r5l_ring_add(log, ctx->pos, BLOCK_SECTORS);
	struct page *page;
	struct r5l_payload_data_parity *payload;
	struct r5l_payload_flush *payload_flush;

	page = alloc_page(GFP_KERNEL);
	if (!page)
		return -ENOMEM;

	while (mb_offset < le32_to_cpu(mb->meta_size)) {
		payload = (void *)mb + mb_offset;
		payload_flush = (void *)mb + mb_offset;

		if (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_DATA) {
			if (r5l_recovery_verify_data_checksum(
				    log, ctx, page, log_offset,
				    payload->checksum[0]) < 0)
				goto mismatch;
		} else if (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_PARITY) {
			if (r5l_recovery_verify_data_checksum(
				    log, ctx, page, log_offset,
				    payload->checksum[0]) < 0)
				goto mismatch;
			if (conf->max_degraded == 2 && /* q for RAID 6 */
			    r5l_recovery_verify_data_checksum(
				    log, ctx, page,
				    r5l_ring_add(log, log_offset,
						 BLOCK_SECTORS),
				    payload->checksum[1]) < 0)
				goto mismatch;
		} else if (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_FLUSH) {
			/* nothing to do for R5LOG_PAYLOAD_FLUSH here */
		} else /* not R5LOG_PAYLOAD_DATA/PARITY/FLUSH */
			goto mismatch;

		if (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_FLUSH) {
			mb_offset += sizeof(struct r5l_payload_flush) +
				le32_to_cpu(payload_flush->size);
		} else {
			/* DATA or PARITY payload */
			log_offset = r5l_ring_add(log, log_offset,
						  le32_to_cpu(payload->size));
			mb_offset += sizeof(struct r5l_payload_data_parity) +
				sizeof(__le32) *
				(le32_to_cpu(payload->size) >> (PAGE_SHIFT - 9));
		}

	}

	put_page(page);
	return 0;

mismatch:
	put_page(page);
	return -EINVAL;
}