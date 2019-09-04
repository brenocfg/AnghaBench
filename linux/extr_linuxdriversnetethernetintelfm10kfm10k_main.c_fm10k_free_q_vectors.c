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
struct fm10k_intfc {int num_q_vectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_free_q_vector (struct fm10k_intfc*,int) ; 
 int /*<<< orphan*/  fm10k_reset_num_queues (struct fm10k_intfc*) ; 

__attribute__((used)) static void fm10k_free_q_vectors(struct fm10k_intfc *interface)
{
	int v_idx = interface->num_q_vectors;

	fm10k_reset_num_queues(interface);

	while (v_idx--)
		fm10k_free_q_vector(interface, v_idx);
}