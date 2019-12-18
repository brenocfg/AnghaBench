#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* out; void* in; } ;
struct TYPE_4__ {TYPE_1__ data; struct pvcalls_data_intf* ring; } ;
struct sock_mapping {TYPE_2__ active; } ;
struct pvcalls_data_intf {int /*<<< orphan*/  ring_order; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PVCALLS_RING_ORDER ; 
 int XEN_FLEX_RING_SIZE (int /*<<< orphan*/ ) ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_active_ring (struct sock_mapping*) ; 
 scalar_t__ get_zeroed_page (int) ; 

__attribute__((used)) static int alloc_active_ring(struct sock_mapping *map)
{
	void *bytes;

	map->active.ring = (struct pvcalls_data_intf *)
		get_zeroed_page(GFP_KERNEL);
	if (!map->active.ring)
		goto out;

	map->active.ring->ring_order = PVCALLS_RING_ORDER;
	bytes = (void *)__get_free_pages(GFP_KERNEL | __GFP_ZERO,
					PVCALLS_RING_ORDER);
	if (!bytes)
		goto out;

	map->active.data.in = bytes;
	map->active.data.out = bytes +
		XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER);

	return 0;

out:
	free_active_ring(map);
	return -ENOMEM;
}