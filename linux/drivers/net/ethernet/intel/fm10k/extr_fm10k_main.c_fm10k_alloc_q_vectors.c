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
struct fm10k_intfc {unsigned int num_q_vectors; unsigned int num_rx_queues; unsigned int num_tx_queues; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int ENOMEM ; 
 int fm10k_alloc_q_vector (struct fm10k_intfc*,unsigned int,unsigned int,int,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  fm10k_free_q_vector (struct fm10k_intfc*,unsigned int) ; 
 int /*<<< orphan*/  fm10k_reset_num_queues (struct fm10k_intfc*) ; 

__attribute__((used)) static int fm10k_alloc_q_vectors(struct fm10k_intfc *interface)
{
	unsigned int q_vectors = interface->num_q_vectors;
	unsigned int rxr_remaining = interface->num_rx_queues;
	unsigned int txr_remaining = interface->num_tx_queues;
	unsigned int rxr_idx = 0, txr_idx = 0, v_idx = 0;
	int err;

	if (q_vectors >= (rxr_remaining + txr_remaining)) {
		for (; rxr_remaining; v_idx++) {
			err = fm10k_alloc_q_vector(interface, q_vectors, v_idx,
						   0, 0, 1, rxr_idx);
			if (err)
				goto err_out;

			/* update counts and index */
			rxr_remaining--;
			rxr_idx++;
		}
	}

	for (; v_idx < q_vectors; v_idx++) {
		int rqpv = DIV_ROUND_UP(rxr_remaining, q_vectors - v_idx);
		int tqpv = DIV_ROUND_UP(txr_remaining, q_vectors - v_idx);

		err = fm10k_alloc_q_vector(interface, q_vectors, v_idx,
					   tqpv, txr_idx,
					   rqpv, rxr_idx);

		if (err)
			goto err_out;

		/* update counts and index */
		rxr_remaining -= rqpv;
		txr_remaining -= tqpv;
		rxr_idx++;
		txr_idx++;
	}

	return 0;

err_out:
	fm10k_reset_num_queues(interface);

	while (v_idx--)
		fm10k_free_q_vector(interface, v_idx);

	return -ENOMEM;
}