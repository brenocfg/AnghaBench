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
struct etnaviv_cmdbuf_suballoc {int free_space; int /*<<< orphan*/  free_event; int /*<<< orphan*/  lock; int /*<<< orphan*/  granule_map; } ;
struct etnaviv_cmdbuf {int suballoc_offset; int /*<<< orphan*/  size; struct etnaviv_cmdbuf_suballoc* suballoc; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int SUBALLOC_GRANULE ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int order_base_2 (int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void etnaviv_cmdbuf_free(struct etnaviv_cmdbuf *cmdbuf)
{
	struct etnaviv_cmdbuf_suballoc *suballoc = cmdbuf->suballoc;
	int order = order_base_2(ALIGN(cmdbuf->size, SUBALLOC_GRANULE) /
				 SUBALLOC_GRANULE);

	mutex_lock(&suballoc->lock);
	bitmap_release_region(suballoc->granule_map,
			      cmdbuf->suballoc_offset / SUBALLOC_GRANULE,
			      order);
	suballoc->free_space = 1;
	mutex_unlock(&suballoc->lock);
	wake_up_all(&suballoc->free_event);
}