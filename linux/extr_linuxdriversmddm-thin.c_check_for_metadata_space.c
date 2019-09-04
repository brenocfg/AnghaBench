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
struct pool {int /*<<< orphan*/  pmd; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,char const*) ; 
 int /*<<< orphan*/  PM_OUT_OF_METADATA_SPACE ; 
 int dm_pool_get_free_metadata_block_count (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_read_only (struct pool*) ; 
 int /*<<< orphan*/  set_pool_mode (struct pool*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_for_metadata_space(struct pool *pool)
{
	int r;
	const char *ooms_reason = NULL;
	dm_block_t nr_free;

	r = dm_pool_get_free_metadata_block_count(pool->pmd, &nr_free);
	if (r)
		ooms_reason = "Could not get free metadata blocks";
	else if (!nr_free)
		ooms_reason = "No free metadata blocks";

	if (ooms_reason && !is_read_only(pool)) {
		DMERR("%s", ooms_reason);
		set_pool_mode(pool, PM_OUT_OF_METADATA_SPACE);
	}
}