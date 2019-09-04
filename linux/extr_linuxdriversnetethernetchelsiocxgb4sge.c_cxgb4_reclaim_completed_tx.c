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
struct sge_txq {int in_use; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int MAX_TX_RECLAIM ; 
 int /*<<< orphan*/  free_tx_desc (struct adapter*,struct sge_txq*,int,int) ; 
 int reclaimable (struct sge_txq*) ; 

inline void cxgb4_reclaim_completed_tx(struct adapter *adap, struct sge_txq *q,
					bool unmap)
{
	int avail = reclaimable(q);

	if (avail) {
		/*
		 * Limit the amount of clean up work we do at a time to keep
		 * the Tx lock hold time O(1).
		 */
		if (avail > MAX_TX_RECLAIM)
			avail = MAX_TX_RECLAIM;

		free_tx_desc(adap, q, avail, unmap);
		q->in_use -= avail;
	}
}