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
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {int dummy; } ;

/* Variables and functions */
 int allocate_vnic_ctxt (struct hfi1_devdata*,struct hfi1_ctxtdata**) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int) ; 
 int /*<<< orphan*/  deallocate_vnic_ctxt (struct hfi1_devdata*,struct hfi1_ctxtdata*) ; 
 int setup_vnic_ctxt (struct hfi1_devdata*,struct hfi1_ctxtdata*) ; 

__attribute__((used)) static int hfi1_vnic_allot_ctxt(struct hfi1_devdata *dd,
				struct hfi1_ctxtdata **vnic_ctxt)
{
	int rc;

	rc = allocate_vnic_ctxt(dd, vnic_ctxt);
	if (rc) {
		dd_dev_err(dd, "vnic ctxt alloc failed %d\n", rc);
		return rc;
	}

	rc = setup_vnic_ctxt(dd, *vnic_ctxt);
	if (rc) {
		dd_dev_err(dd, "vnic ctxt setup failed %d\n", rc);
		deallocate_vnic_ctxt(dd, *vnic_ctxt);
		*vnic_ctxt = NULL;
	}

	return rc;
}