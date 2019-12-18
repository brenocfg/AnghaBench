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
struct r5l_recovery_ctx {int dummy; } ;
struct r5l_log {int /*<<< orphan*/  uuid_checksum; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ crc32c_le (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5l_recovery_read_page (struct r5l_log*,struct r5l_recovery_ctx*,struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
r5l_recovery_verify_data_checksum(struct r5l_log *log,
				  struct r5l_recovery_ctx *ctx,
				  struct page *page,
				  sector_t log_offset, __le32 log_checksum)
{
	void *addr;
	u32 checksum;

	r5l_recovery_read_page(log, ctx, page, log_offset);
	addr = kmap_atomic(page);
	checksum = crc32c_le(log->uuid_checksum, addr, PAGE_SIZE);
	kunmap_atomic(addr);
	return (le32_to_cpu(log_checksum) == checksum) ? 0 : -EINVAL;
}