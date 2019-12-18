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
struct dm_cache_metadata {scalar_t__ fail_io; } ;
typedef  int /*<<< orphan*/  flags_mutator ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WRITE_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  WRITE_UNLOCK (struct dm_cache_metadata*) ; 
 int __begin_transaction (struct dm_cache_metadata*) ; 
 int __commit_transaction (struct dm_cache_metadata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_clean_shutdown ; 
 int /*<<< orphan*/  set_clean_shutdown ; 

int dm_cache_commit(struct dm_cache_metadata *cmd, bool clean_shutdown)
{
	int r = -EINVAL;
	flags_mutator mutator = (clean_shutdown ? set_clean_shutdown :
				 clear_clean_shutdown);

	WRITE_LOCK(cmd);
	if (cmd->fail_io)
		goto out;

	r = __commit_transaction(cmd, mutator);
	if (r)
		goto out;

	r = __begin_transaction(cmd);
out:
	WRITE_UNLOCK(cmd);
	return r;
}