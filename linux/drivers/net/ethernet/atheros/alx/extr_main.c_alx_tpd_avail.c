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
struct alx_tx_queue {scalar_t__ write_idx; scalar_t__ read_idx; int count; } ;

/* Variables and functions */

__attribute__((used)) static inline int alx_tpd_avail(struct alx_tx_queue *txq)
{
	if (txq->write_idx >= txq->read_idx)
		return txq->count + txq->read_idx - txq->write_idx - 1;
	return txq->read_idx - txq->write_idx - 1;
}