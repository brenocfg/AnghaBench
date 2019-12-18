#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sge_uld_rxq_info {unsigned int nrxq; unsigned int nciq; unsigned short* rspq_id; int* msix_tbl; struct sge_ofld_rxq* uldrxq; } ;
struct TYPE_12__ {scalar_t__ size; } ;
struct TYPE_11__ {unsigned short abs_id; scalar_t__ desc; } ;
struct sge_ofld_rxq {TYPE_5__ fl; TYPE_4__ rspq; int /*<<< orphan*/  stats; } ;
struct TYPE_8__ {scalar_t__ abs_id; } ;
struct sge {TYPE_1__ intrq; } ;
struct TYPE_9__ {unsigned int nports; } ;
struct adapter {int flags; int /*<<< orphan*/ * port; TYPE_3__* msix_info_ulds; TYPE_2__ params; struct sge sge; } ;
struct TYPE_10__ {int idx; } ;

/* Variables and functions */
 int CXGB4_USING_MSIX ; 
 int ENOSPC ; 
 int /*<<< orphan*/  free_rspq_fl (struct adapter*,TYPE_4__*,TYPE_5__*) ; 
 int get_msix_idx_from_bmap (struct adapter*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int t4_sge_alloc_rxq (struct adapter*,TYPE_4__*,int,int /*<<< orphan*/ ,int,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uldrx_flush_handler ; 
 int /*<<< orphan*/  uldrx_handler ; 

__attribute__((used)) static int alloc_uld_rxqs(struct adapter *adap,
			  struct sge_uld_rxq_info *rxq_info, bool lro)
{
	unsigned int nq = rxq_info->nrxq + rxq_info->nciq;
	int i, err, msi_idx, que_idx = 0, bmap_idx = 0;
	struct sge_ofld_rxq *q = rxq_info->uldrxq;
	unsigned short *ids = rxq_info->rspq_id;
	struct sge *s = &adap->sge;
	unsigned int per_chan;

	per_chan = rxq_info->nrxq / adap->params.nports;

	if (adap->flags & CXGB4_USING_MSIX)
		msi_idx = 1;
	else
		msi_idx = -((int)s->intrq.abs_id + 1);

	for (i = 0; i < nq; i++, q++) {
		if (i == rxq_info->nrxq) {
			/* start allocation of concentrator queues */
			per_chan = rxq_info->nciq / adap->params.nports;
			que_idx = 0;
		}

		if (msi_idx >= 0) {
			bmap_idx = get_msix_idx_from_bmap(adap);
			if (bmap_idx < 0) {
				err = -ENOSPC;
				goto freeout;
			}
			msi_idx = adap->msix_info_ulds[bmap_idx].idx;
		}
		err = t4_sge_alloc_rxq(adap, &q->rspq, false,
				       adap->port[que_idx++ / per_chan],
				       msi_idx,
				       q->fl.size ? &q->fl : NULL,
				       uldrx_handler,
				       lro ? uldrx_flush_handler : NULL,
				       0);
		if (err)
			goto freeout;
		if (msi_idx >= 0)
			rxq_info->msix_tbl[i] = bmap_idx;
		memset(&q->stats, 0, sizeof(q->stats));
		if (ids)
			ids[i] = q->rspq.abs_id;
	}
	return 0;
freeout:
	q = rxq_info->uldrxq;
	for ( ; i; i--, q++) {
		if (q->rspq.desc)
			free_rspq_fl(adap, &q->rspq,
				     q->fl.size ? &q->fl : NULL);
	}
	return err;
}