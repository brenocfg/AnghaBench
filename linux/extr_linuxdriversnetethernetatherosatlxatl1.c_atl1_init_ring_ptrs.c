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
struct atl1_tpd_ring {int /*<<< orphan*/  next_to_clean; int /*<<< orphan*/  next_to_use; } ;
struct atl1_rrd_ring {int /*<<< orphan*/  next_to_clean; scalar_t__ next_to_use; } ;
struct atl1_rfd_ring {int /*<<< orphan*/  next_to_use; scalar_t__ next_to_clean; } ;
struct atl1_adapter {struct atl1_rrd_ring rrd_ring; struct atl1_rfd_ring rfd_ring; struct atl1_tpd_ring tpd_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1_init_ring_ptrs(struct atl1_adapter *adapter)
{
	struct atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	struct atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	struct atl1_rrd_ring *rrd_ring = &adapter->rrd_ring;

	atomic_set(&tpd_ring->next_to_use, 0);
	atomic_set(&tpd_ring->next_to_clean, 0);

	rfd_ring->next_to_clean = 0;
	atomic_set(&rfd_ring->next_to_use, 0);

	rrd_ring->next_to_use = 0;
	atomic_set(&rrd_ring->next_to_clean, 0);
}