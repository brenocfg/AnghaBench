#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  itr; } ;
struct ixgbe_q_vector {int itr; TYPE_1__ tx; TYPE_1__ rx; } ;

/* Variables and functions */
 int IXGBE_ITR_ADAPTIVE_LATENCY ; 
 int /*<<< orphan*/  ixgbe_update_itr (struct ixgbe_q_vector*,TYPE_1__*) ; 
 int /*<<< orphan*/  ixgbe_write_eitr (struct ixgbe_q_vector*) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_set_itr(struct ixgbe_q_vector *q_vector)
{
	u32 new_itr;

	ixgbe_update_itr(q_vector, &q_vector->tx);
	ixgbe_update_itr(q_vector, &q_vector->rx);

	/* use the smallest value of new ITR delay calculations */
	new_itr = min(q_vector->rx.itr, q_vector->tx.itr);

	/* Clear latency flag if set, shift into correct position */
	new_itr &= ~IXGBE_ITR_ADAPTIVE_LATENCY;
	new_itr <<= 2;

	if (new_itr != q_vector->itr) {
		/* save the algorithm value here */
		q_vector->itr = new_itr;

		ixgbe_write_eitr(q_vector);
	}
}