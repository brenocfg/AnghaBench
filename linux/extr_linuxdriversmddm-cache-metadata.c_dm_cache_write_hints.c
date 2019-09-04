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
struct dm_cache_policy {int dummy; } ;
struct dm_cache_metadata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  WRITE_UNLOCK (struct dm_cache_metadata*) ; 
 int write_hints (struct dm_cache_metadata*,struct dm_cache_policy*) ; 

int dm_cache_write_hints(struct dm_cache_metadata *cmd, struct dm_cache_policy *policy)
{
	int r;

	WRITE_LOCK(cmd);
	r = write_hints(cmd, policy);
	WRITE_UNLOCK(cmd);

	return r;
}