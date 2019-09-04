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
struct smq_policy {int /*<<< orphan*/  cache_blocks_per_hotspot_block; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  from_oblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_oblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dm_oblock_t to_hblock(struct smq_policy *mq, dm_oblock_t b)
{
	sector_t r = from_oblock(b);
	(void) sector_div(r, mq->cache_blocks_per_hotspot_block);
	return to_oblock(r);
}