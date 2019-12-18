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
struct TYPE_2__ {scalar_t__ abs_id; } ;
struct sge {TYPE_1__ fw_evtq; TYPE_1__ intrq; int /*<<< orphan*/  egr_sz; int /*<<< orphan*/  txq_maperr; int /*<<< orphan*/  starving_fl; } ;
struct adapter {int flags; int msi_idx; int /*<<< orphan*/ * port; struct sge sge; } ;

/* Variables and functions */
 int CXGB4_USING_MSIX ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fwevtq_handler ; 
 int t4_sge_alloc_rxq (struct adapter*,TYPE_1__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int setup_fw_sge_queues(struct adapter *adap)
{
	struct sge *s = &adap->sge;
	int err = 0;

	bitmap_zero(s->starving_fl, s->egr_sz);
	bitmap_zero(s->txq_maperr, s->egr_sz);

	if (adap->flags & CXGB4_USING_MSIX)
		adap->msi_idx = 1;         /* vector 0 is for non-queue interrupts */
	else {
		err = t4_sge_alloc_rxq(adap, &s->intrq, false, adap->port[0], 0,
				       NULL, NULL, NULL, -1);
		if (err)
			return err;
		adap->msi_idx = -((int)s->intrq.abs_id + 1);
	}

	err = t4_sge_alloc_rxq(adap, &s->fw_evtq, true, adap->port[0],
			       adap->msi_idx, NULL, fwevtq_handler, NULL, -1);
	return err;
}