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
struct rsrc_bmap {int max; int /*<<< orphan*/  bmap; } ;

/* Variables and functions */
 int bitmap_weight (int /*<<< orphan*/ ,int) ; 

int rvu_rsrc_free_count(struct rsrc_bmap *rsrc)
{
	int used;

	if (!rsrc->bmap)
		return 0;

	used = bitmap_weight(rsrc->bmap, rsrc->max);
	return (rsrc->max - used);
}