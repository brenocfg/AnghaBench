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
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rvu_free_rsrc_contig(struct rsrc_bmap *rsrc, int nrsrc, int start)
{
	if (!rsrc->bmap)
		return;
	if (start >= rsrc->max)
		return;

	bitmap_clear(rsrc->bmap, start, nrsrc);
}