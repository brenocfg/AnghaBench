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
struct igb_adapter {int num_q_vectors; int num_rx_queues; int num_tx_queues; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int ENOMEM ; 
 int igb_alloc_q_vector (struct igb_adapter*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  igb_free_q_vector (struct igb_adapter*,int) ; 

__attribute__((used)) static int igb_alloc_q_vectors(struct igb_adapter *adapter)
{
	int q_vectors = adapter->num_q_vectors;
	int rxr_remaining = adapter->num_rx_queues;
	int txr_remaining = adapter->num_tx_queues;
	int rxr_idx = 0, txr_idx = 0, v_idx = 0;
	int err;

	if (q_vectors >= (rxr_remaining + txr_remaining)) {
		for (; rxr_remaining; v_idx++) {
			err = igb_alloc_q_vector(adapter, q_vectors, v_idx,
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

		err = igb_alloc_q_vector(adapter, q_vectors, v_idx,
					 tqpv, txr_idx, rqpv, rxr_idx);

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
	adapter->num_tx_queues = 0;
	adapter->num_rx_queues = 0;
	adapter->num_q_vectors = 0;

	while (v_idx--)
		igb_free_q_vector(adapter, v_idx);

	return -ENOMEM;
}