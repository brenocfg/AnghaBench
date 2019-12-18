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
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 

int rvu_alloc_rsrc(struct rsrc_bmap *rsrc)
{
	int id;

	if (!rsrc->bmap)
		return -EINVAL;

	id = find_first_zero_bit(rsrc->bmap, rsrc->max);
	if (id >= rsrc->max)
		return -ENOSPC;

	__set_bit(id, rsrc->bmap);

	return id;
}