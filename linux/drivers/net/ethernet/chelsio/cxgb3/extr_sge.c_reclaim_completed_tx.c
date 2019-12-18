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
struct sge_txq {unsigned int processed; unsigned int cleaned; unsigned int in_use; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_tx_desc (struct adapter*,struct sge_txq*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static inline unsigned int reclaim_completed_tx(struct adapter *adapter,
						struct sge_txq *q,
						unsigned int chunk)
{
	unsigned int reclaim = q->processed - q->cleaned;

	reclaim = min(chunk, reclaim);
	if (reclaim) {
		free_tx_desc(adapter, q, reclaim);
		q->cleaned += reclaim;
		q->in_use -= reclaim;
	}
	return q->processed - q->cleaned;
}