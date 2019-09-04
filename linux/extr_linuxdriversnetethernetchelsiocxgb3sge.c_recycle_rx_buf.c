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
struct sge_fl {size_t pidx; int gen; size_t size; int /*<<< orphan*/  pend_cred; int /*<<< orphan*/  credits; int /*<<< orphan*/ * sdesc; struct rx_desc* desc; } ;
struct rx_desc {void* gen2; void* len_gen; int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V_FLD_GEN1 (int) ; 
 int /*<<< orphan*/  V_FLD_GEN2 (int) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  ring_fl_db (struct adapter*,struct sge_fl*) ; 

__attribute__((used)) static void recycle_rx_buf(struct adapter *adap, struct sge_fl *q,
			   unsigned int idx)
{
	struct rx_desc *from = &q->desc[idx];
	struct rx_desc *to = &q->desc[q->pidx];

	q->sdesc[q->pidx] = q->sdesc[idx];
	to->addr_lo = from->addr_lo;	/* already big endian */
	to->addr_hi = from->addr_hi;	/* likewise */
	dma_wmb();
	to->len_gen = cpu_to_be32(V_FLD_GEN1(q->gen));
	to->gen2 = cpu_to_be32(V_FLD_GEN2(q->gen));

	if (++q->pidx == q->size) {
		q->pidx = 0;
		q->gen ^= 1;
	}

	q->credits++;
	q->pend_cred++;
	ring_fl_db(adap, q);
}