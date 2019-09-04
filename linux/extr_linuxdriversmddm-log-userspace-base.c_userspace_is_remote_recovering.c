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
struct log_c {scalar_t__ in_sync_hint; int /*<<< orphan*/  uuid; } ;
struct dm_dirty_log {struct log_c* context; } ;
typedef  scalar_t__ region_t ;
typedef  int /*<<< orphan*/  region64 ;
typedef  int /*<<< orphan*/  pkg ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ULOG_IS_REMOTE_RECOVERING ; 
 int HZ ; 
 int jiffies ; 
 scalar_t__ time_after (unsigned long,int) ; 
 int userspace_do_request (struct log_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,size_t*) ; 

__attribute__((used)) static int userspace_is_remote_recovering(struct dm_dirty_log *log,
					  region_t region)
{
	int r;
	uint64_t region64 = region;
	struct log_c *lc = log->context;
	static unsigned long limit;
	struct {
		int64_t is_recovering;
		uint64_t in_sync_hint;
	} pkg;
	size_t rdata_size = sizeof(pkg);

	/*
	 * Once the mirror has been reported to be in-sync,
	 * it will never again ask for recovery work.  So,
	 * we can safely say there is not a remote machine
	 * recovering if the device is in-sync.  (in_sync_hint
	 * must be reset at resume time.)
	 */
	if (region < lc->in_sync_hint)
		return 0;
	else if (time_after(limit, jiffies))
		return 1;

	limit = jiffies + (HZ / 4);
	r = userspace_do_request(lc, lc->uuid, DM_ULOG_IS_REMOTE_RECOVERING,
				 (char *)&region64, sizeof(region64),
				 (char *)&pkg, &rdata_size);
	if (r)
		return 1;

	lc->in_sync_hint = pkg.in_sync_hint;

	return (int)pkg.is_recovering;
}