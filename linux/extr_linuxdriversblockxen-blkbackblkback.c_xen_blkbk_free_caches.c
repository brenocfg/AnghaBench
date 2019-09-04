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
struct xen_blkif_ring {scalar_t__ persistent_gnt_c; int /*<<< orphan*/  persistent_gnts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_persistent_gnts (struct xen_blkif_ring*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  shrink_free_pagepool (struct xen_blkif_ring*,int /*<<< orphan*/ ) ; 

void xen_blkbk_free_caches(struct xen_blkif_ring *ring)
{
	/* Free all persistent grant pages */
	if (!RB_EMPTY_ROOT(&ring->persistent_gnts))
		free_persistent_gnts(ring, &ring->persistent_gnts,
			ring->persistent_gnt_c);

	BUG_ON(!RB_EMPTY_ROOT(&ring->persistent_gnts));
	ring->persistent_gnt_c = 0;

	/* Since we are shutting down remove all pages from the buffer */
	shrink_free_pagepool(ring, 0 /* All */);
}