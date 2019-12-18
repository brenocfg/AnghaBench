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
struct mtd_info {struct map_info* priv; } ;
struct map_info {int dummy; } ;
struct erase_info {unsigned long len; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  map_word ;

/* Variables and functions */
 scalar_t__ map_bankwidth (struct map_info*) ; 
 int /*<<< orphan*/  map_word_ff (struct map_info*) ; 
 int /*<<< orphan*/  map_write (struct map_info*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mapram_erase (struct mtd_info *mtd, struct erase_info *instr)
{
	/* Yeah, it's inefficient. Who cares? It's faster than a _real_
	   flash erase. */
	struct map_info *map = mtd->priv;
	map_word allff;
	unsigned long i;

	allff = map_word_ff(map);
	for (i=0; i<instr->len; i += map_bankwidth(map))
		map_write(map, allff, instr->addr + i);
	return 0;
}