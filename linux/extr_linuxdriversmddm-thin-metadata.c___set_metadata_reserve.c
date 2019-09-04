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
struct dm_pool_metadata {int metadata_reserve; int /*<<< orphan*/  metadata_sm; } ;
typedef  int dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  div_u64 (int,int) ; 
 int dm_sm_get_nr_blocks (int /*<<< orphan*/ ,int*) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __set_metadata_reserve(struct dm_pool_metadata *pmd)
{
	int r;
	dm_block_t total;
	dm_block_t max_blocks = 4096; /* 16M */

	r = dm_sm_get_nr_blocks(pmd->metadata_sm, &total);
	if (r) {
		DMERR("could not get size of metadata device");
		pmd->metadata_reserve = max_blocks;
	} else
		pmd->metadata_reserve = min(max_blocks, div_u64(total, 10));
}