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
struct hfi1_vnic_vport_info {struct hfi1_devdata* dd; } ;
struct TYPE_2__ {scalar_t__ num_vports; int num_ctxt; int /*<<< orphan*/ ** ctxt; } ;
struct hfi1_devdata {TYPE_1__ vnic; } ;

/* Variables and functions */
 int /*<<< orphan*/  deallocate_vnic_ctxt (struct hfi1_devdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_deinit_vnic_rsm (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  hfi1_mutex ; 
 int /*<<< orphan*/  hfi1_rcd_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_vnic_txreq_deinit (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hfi1_vnic_deinit(struct hfi1_vnic_vport_info *vinfo)
{
	struct hfi1_devdata *dd = vinfo->dd;
	int i;

	mutex_lock(&hfi1_mutex);
	if (--dd->vnic.num_vports == 0) {
		for (i = 0; i < dd->vnic.num_ctxt; i++) {
			deallocate_vnic_ctxt(dd, dd->vnic.ctxt[i]);
			hfi1_rcd_put(dd->vnic.ctxt[i]);
			dd->vnic.ctxt[i] = NULL;
		}
		hfi1_deinit_vnic_rsm(dd);
		dd->vnic.num_ctxt = 0;
		hfi1_vnic_txreq_deinit(dd);
	}
	mutex_unlock(&hfi1_mutex);
}