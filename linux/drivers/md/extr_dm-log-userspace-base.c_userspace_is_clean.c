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
typedef  int /*<<< orphan*/  uint64_t ;
struct log_c {int /*<<< orphan*/  uuid; } ;
struct dm_dirty_log {struct log_c* context; } ;
typedef  int /*<<< orphan*/  region_t ;
typedef  int /*<<< orphan*/  region64 ;
typedef  int /*<<< orphan*/  is_clean ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ULOG_IS_CLEAN ; 
 int userspace_do_request (struct log_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,size_t*) ; 

__attribute__((used)) static int userspace_is_clean(struct dm_dirty_log *log, region_t region)
{
	int r;
	uint64_t region64 = (uint64_t)region;
	int64_t is_clean;
	size_t rdata_size;
	struct log_c *lc = log->context;

	rdata_size = sizeof(is_clean);
	r = userspace_do_request(lc, lc->uuid, DM_ULOG_IS_CLEAN,
				 (char *)&region64, sizeof(region64),
				 (char *)&is_clean, &rdata_size);

	return (r) ? 0 : (int)is_clean;
}