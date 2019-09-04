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
struct dm_cell_key_v2 {void* block_end; void* block_begin; scalar_t__ dev; scalar_t__ virtual; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 void* from_oblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_key(dm_oblock_t begin, dm_oblock_t end, struct dm_cell_key_v2 *key)
{
	key->virtual = 0;
	key->dev = 0;
	key->block_begin = from_oblock(begin);
	key->block_end = from_oblock(end);
}