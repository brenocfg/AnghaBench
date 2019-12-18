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
struct dm_cache_metadata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_LOCK_VOID (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  READ_UNLOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  __dump_mappings (struct dm_cache_metadata*) ; 

void dm_cache_dump(struct dm_cache_metadata *cmd)
{
	READ_LOCK_VOID(cmd);
	__dump_mappings(cmd);
	READ_UNLOCK(cmd);
}