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
struct era_metadata {int /*<<< orphan*/  bm; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUPERBLOCK_LOCATION ; 
 int dm_bm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int /*<<< orphan*/  sb_validator ; 

__attribute__((used)) static int superblock_read_lock(struct era_metadata *md,
				struct dm_block **sblock)
{
	return dm_bm_read_lock(md->bm, SUPERBLOCK_LOCATION,
			       &sb_validator, sblock);
}