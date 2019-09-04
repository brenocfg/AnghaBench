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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  sync_count ;
struct log_c {scalar_t__ region_count; scalar_t__ in_sync_hint; int /*<<< orphan*/  uuid; } ;
struct dm_dirty_log {struct log_c* context; } ;
typedef  int /*<<< orphan*/  region_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ULOG_GET_SYNC_COUNT ; 
 int userspace_do_request (struct log_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t*) ; 

__attribute__((used)) static region_t userspace_get_sync_count(struct dm_dirty_log *log)
{
	int r;
	size_t rdata_size;
	uint64_t sync_count;
	struct log_c *lc = log->context;

	rdata_size = sizeof(sync_count);
	r = userspace_do_request(lc, lc->uuid, DM_ULOG_GET_SYNC_COUNT,
				 NULL, 0, (char *)&sync_count, &rdata_size);

	if (r)
		return 0;

	if (sync_count >= lc->region_count)
		lc->in_sync_hint = lc->region_count;

	return (region_t)sync_count;
}