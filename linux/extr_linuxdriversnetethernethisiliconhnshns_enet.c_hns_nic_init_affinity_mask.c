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
struct hnae_ring {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_tx_ring (struct hnae_ring*) ; 
 int num_possible_cpus () ; 

__attribute__((used)) static int hns_nic_init_affinity_mask(int q_num, int ring_idx,
				      struct hnae_ring *ring, cpumask_t *mask)
{
	int cpu;

	/* Diffrent irq banlance between 16core and 32core.
	 * The cpu mask set by ring index according to the ring flag
	 * which indicate the ring is tx or rx.
	 */
	if (q_num == num_possible_cpus()) {
		if (is_tx_ring(ring))
			cpu = ring_idx;
		else
			cpu = ring_idx - q_num;
	} else {
		if (is_tx_ring(ring))
			cpu = ring_idx * 2;
		else
			cpu = (ring_idx - q_num) * 2 + 1;
	}

	cpumask_clear(mask);
	cpumask_set_cpu(cpu, mask);

	return cpu;
}