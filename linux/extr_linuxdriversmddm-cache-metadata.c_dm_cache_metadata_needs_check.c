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
struct dm_cache_metadata {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEEDS_CHECK ; 
 int /*<<< orphan*/  READ_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  READ_UNLOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dm_cache_metadata_needs_check(struct dm_cache_metadata *cmd, bool *result)
{
	READ_LOCK(cmd);
	*result = !!test_bit(NEEDS_CHECK, &cmd->flags);
	READ_UNLOCK(cmd);

	return 0;
}