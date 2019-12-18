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
typedef  int u32 ;
struct sge_rspq {int cidx; int size; int gen; int credits; int /*<<< orphan*/  pure_rsps; struct rsp_desc* desc; } ;
struct sge_qset {scalar_t__ txq_stopped; struct sge_rspq rspq; } ;
struct rsp_desc {int /*<<< orphan*/  flags; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int RSPD_CTRL_MASK ; 
 int RSPD_GTS_MASK ; 
 int /*<<< orphan*/  check_ring_db (struct adapter*,struct sge_qset*,unsigned int) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  handle_rsp_cntrl_info (struct sge_qset*,int) ; 
 int is_new_response (struct rsp_desc*,struct sge_rspq*) ; 
 scalar_t__ is_pure_response (struct rsp_desc*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (struct rsp_desc*) ; 
 int /*<<< orphan*/  refill_rspq (struct adapter*,struct sge_rspq*,int) ; 
 int /*<<< orphan*/  restart_tx (struct sge_qset*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int process_pure_responses(struct adapter *adap, struct sge_qset *qs,
				  struct rsp_desc *r)
{
	struct sge_rspq *q = &qs->rspq;
	unsigned int sleeping = 0;

	do {
		u32 flags = ntohl(r->flags);

		r++;
		if (unlikely(++q->cidx == q->size)) {
			q->cidx = 0;
			q->gen ^= 1;
			r = q->desc;
		}
		prefetch(r);

		if (flags & RSPD_CTRL_MASK) {
			sleeping |= flags & RSPD_GTS_MASK;
			handle_rsp_cntrl_info(qs, flags);
		}

		q->pure_rsps++;
		if (++q->credits >= (q->size / 4)) {
			refill_rspq(adap, q, q->credits);
			q->credits = 0;
		}
		if (!is_new_response(r, q))
			break;
		dma_rmb();
	} while (is_pure_response(r));

	if (sleeping)
		check_ring_db(adap, qs, sleeping);

	smp_mb();		/* commit Tx queue .processed updates */
	if (unlikely(qs->txq_stopped != 0))
		restart_tx(qs);

	return is_new_response(r, q);
}