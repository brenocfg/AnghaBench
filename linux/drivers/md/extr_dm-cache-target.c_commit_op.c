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
struct cache {int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  commit (struct cache*,int) ; 
 scalar_t__ dm_cache_changed_this_transaction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno_to_blk_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t commit_op(void *context)
{
	struct cache *cache = context;

	if (dm_cache_changed_this_transaction(cache->cmd))
		return errno_to_blk_status(commit(cache, false));

	return 0;
}