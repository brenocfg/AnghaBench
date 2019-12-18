#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hfi1_vnic_vport_info {int num_rx_q; struct hfi1_devdata* dd; } ;
struct TYPE_6__ {int num_ctxt; int /*<<< orphan*/  num_vports; TYPE_2__** ctxt; } ;
struct hfi1_devdata {TYPE_1__ vnic; } ;
struct TYPE_7__ {int vnic_q_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  deallocate_vnic_ctxt (struct hfi1_devdata*,TYPE_2__*) ; 
 int /*<<< orphan*/  hfi1_init_vnic_rsm (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_mutex ; 
 int /*<<< orphan*/  hfi1_rcd_get (TYPE_2__*) ; 
 int /*<<< orphan*/  hfi1_rcd_put (TYPE_2__*) ; 
 int hfi1_vnic_allot_ctxt (struct hfi1_devdata*,TYPE_2__**) ; 
 int /*<<< orphan*/  hfi1_vnic_sdma_init (struct hfi1_vnic_vport_info*) ; 
 int /*<<< orphan*/  hfi1_vnic_txreq_deinit (struct hfi1_devdata*) ; 
 int hfi1_vnic_txreq_init (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfi1_vnic_init(struct hfi1_vnic_vport_info *vinfo)
{
	struct hfi1_devdata *dd = vinfo->dd;
	int i, rc = 0;

	mutex_lock(&hfi1_mutex);
	if (!dd->vnic.num_vports) {
		rc = hfi1_vnic_txreq_init(dd);
		if (rc)
			goto txreq_fail;
	}

	for (i = dd->vnic.num_ctxt; i < vinfo->num_rx_q; i++) {
		rc = hfi1_vnic_allot_ctxt(dd, &dd->vnic.ctxt[i]);
		if (rc)
			break;
		hfi1_rcd_get(dd->vnic.ctxt[i]);
		dd->vnic.ctxt[i]->vnic_q_idx = i;
	}

	if (i < vinfo->num_rx_q) {
		/*
		 * If required amount of contexts is not
		 * allocated successfully then remaining contexts
		 * are released.
		 */
		while (i-- > dd->vnic.num_ctxt) {
			deallocate_vnic_ctxt(dd, dd->vnic.ctxt[i]);
			hfi1_rcd_put(dd->vnic.ctxt[i]);
			dd->vnic.ctxt[i] = NULL;
		}
		goto alloc_fail;
	}

	if (dd->vnic.num_ctxt != i) {
		dd->vnic.num_ctxt = i;
		hfi1_init_vnic_rsm(dd);
	}

	dd->vnic.num_vports++;
	hfi1_vnic_sdma_init(vinfo);
alloc_fail:
	if (!dd->vnic.num_vports)
		hfi1_vnic_txreq_deinit(dd);
txreq_fail:
	mutex_unlock(&hfi1_mutex);
	return rc;
}