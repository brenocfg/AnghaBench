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
struct ena_ring {int cpu; int /*<<< orphan*/  ena_com_io_cq; } ;

/* Variables and functions */
 int NUMA_NO_NODE ; 
 int cpu_to_node (int) ; 
 int /*<<< orphan*/  ena_com_update_numa_node (int /*<<< orphan*/ ,int) ; 
 int get_cpu () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  put_cpu () ; 

__attribute__((used)) static void ena_update_ring_numa_node(struct ena_ring *tx_ring,
					     struct ena_ring *rx_ring)
{
	int cpu = get_cpu();
	int numa_node;

	/* Check only one ring since the 2 rings are running on the same cpu */
	if (likely(tx_ring->cpu == cpu))
		goto out;

	numa_node = cpu_to_node(cpu);
	put_cpu();

	if (numa_node != NUMA_NO_NODE) {
		ena_com_update_numa_node(tx_ring->ena_com_io_cq, numa_node);
		ena_com_update_numa_node(rx_ring->ena_com_io_cq, numa_node);
	}

	tx_ring->cpu = cpu;
	rx_ring->cpu = cpu;

	return;
out:
	put_cpu();
}