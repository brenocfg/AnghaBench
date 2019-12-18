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
struct log_c {int /*<<< orphan*/  uuid; } ;
struct dm_dirty_log {struct log_c* context; } ;
typedef  int /*<<< orphan*/  region_t ;
typedef  int /*<<< orphan*/  pkg ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ULOG_SET_REGION_SYNC ; 
 int /*<<< orphan*/  userspace_do_request (struct log_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void userspace_set_region_sync(struct dm_dirty_log *log,
				      region_t region, int in_sync)
{
	struct log_c *lc = log->context;
	struct {
		region_t r;
		int64_t i;
	} pkg;

	pkg.r = region;
	pkg.i = (int64_t)in_sync;

	(void) userspace_do_request(lc, lc->uuid, DM_ULOG_SET_REGION_SYNC,
				    (char *)&pkg, sizeof(pkg), NULL, NULL);

	/*
	 * It would be nice to be able to report failures.
	 * However, it is easy enough to detect and resolve.
	 */
	return;
}