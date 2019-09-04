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
struct xen_blkif_ring {int /*<<< orphan*/  inflight; struct xen_blkif* blkif; } ;
struct xen_blkif {int /*<<< orphan*/  drain; int /*<<< orphan*/  drain_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_blk_drain_io(struct xen_blkif_ring *ring)
{
	struct xen_blkif *blkif = ring->blkif;

	atomic_set(&blkif->drain, 1);
	do {
		if (atomic_read(&ring->inflight) == 0)
			break;
		wait_for_completion_interruptible_timeout(
				&blkif->drain_complete, HZ);

		if (!atomic_read(&blkif->drain))
			break;
	} while (!kthread_should_stop());
	atomic_set(&blkif->drain, 0);
}