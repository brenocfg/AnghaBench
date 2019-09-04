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
struct pool {int /*<<< orphan*/  pmd; int /*<<< orphan*/  pool_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,char const*) ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*,char const*) ; 
 int /*<<< orphan*/  PM_FAIL ; 
 char* dm_device_name (int /*<<< orphan*/ ) ; 
 scalar_t__ dm_pool_abort_metadata (int /*<<< orphan*/ ) ; 
 scalar_t__ dm_pool_metadata_set_needs_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pool_mode (struct pool*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void abort_transaction(struct pool *pool)
{
	const char *dev_name = dm_device_name(pool->pool_md);

	DMERR_LIMIT("%s: aborting current metadata transaction", dev_name);
	if (dm_pool_abort_metadata(pool->pmd)) {
		DMERR("%s: failed to abort metadata transaction", dev_name);
		set_pool_mode(pool, PM_FAIL);
	}

	if (dm_pool_metadata_set_needs_check(pool->pmd)) {
		DMERR("%s: failed to set 'needs_check' flag in metadata", dev_name);
		set_pool_mode(pool, PM_FAIL);
	}
}