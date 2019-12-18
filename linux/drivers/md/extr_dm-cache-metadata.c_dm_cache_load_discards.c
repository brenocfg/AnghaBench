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
typedef  int /*<<< orphan*/  load_discard_fn ;

/* Variables and functions */
 int /*<<< orphan*/  READ_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  READ_UNLOCK (struct dm_cache_metadata*) ; 
 int __load_discards (struct dm_cache_metadata*,int /*<<< orphan*/ ,void*) ; 

int dm_cache_load_discards(struct dm_cache_metadata *cmd,
			   load_discard_fn fn, void *context)
{
	int r;

	READ_LOCK(cmd);
	r = __load_discards(cmd, fn, context);
	READ_UNLOCK(cmd);

	return r;
}