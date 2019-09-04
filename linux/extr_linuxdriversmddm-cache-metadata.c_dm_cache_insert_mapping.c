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
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  WRITE_UNLOCK (struct dm_cache_metadata*) ; 
 int __insert (struct dm_cache_metadata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dm_cache_insert_mapping(struct dm_cache_metadata *cmd,
			    dm_cblock_t cblock, dm_oblock_t oblock)
{
	int r;

	WRITE_LOCK(cmd);
	r = __insert(cmd, cblock, oblock);
	WRITE_UNLOCK(cmd);

	return r;
}