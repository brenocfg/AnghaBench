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
struct cache {int dummy; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_dblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_oblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oblocks_per_dblock (struct cache*) ; 
 int /*<<< orphan*/  to_dblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dm_dblock_t oblock_to_dblock(struct cache *cache, dm_oblock_t oblock)
{
	return to_dblock(block_div(from_oblock(oblock),
				   oblocks_per_dblock(cache)));
}