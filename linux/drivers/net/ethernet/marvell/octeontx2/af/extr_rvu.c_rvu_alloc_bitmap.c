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
struct rsrc_bmap {int /*<<< orphan*/  bmap; int /*<<< orphan*/  max; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int rvu_alloc_bitmap(struct rsrc_bmap *rsrc)
{
	rsrc->bmap = kcalloc(BITS_TO_LONGS(rsrc->max),
			     sizeof(long), GFP_KERNEL);
	if (!rsrc->bmap)
		return -ENOMEM;
	return 0;
}