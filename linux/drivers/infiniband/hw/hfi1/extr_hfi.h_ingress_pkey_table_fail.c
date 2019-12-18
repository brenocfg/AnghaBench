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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hfi1_pportdata {int /*<<< orphan*/  port_rcv_constraint_errors; struct hfi1_devdata* dd; } ;
struct TYPE_2__ {int status; int /*<<< orphan*/  pkey; int /*<<< orphan*/  slid; } ;
struct hfi1_devdata {TYPE_1__ err_info_rcv_constraint; } ;

/* Variables and functions */
 int OPA_EI_STATUS_SMASK ; 
 int /*<<< orphan*/  incr_cntr64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ingress_pkey_table_fail(struct hfi1_pportdata *ppd, u16 pkey,
				    u32 slid)
{
	struct hfi1_devdata *dd = ppd->dd;

	incr_cntr64(&ppd->port_rcv_constraint_errors);
	if (!(dd->err_info_rcv_constraint.status & OPA_EI_STATUS_SMASK)) {
		dd->err_info_rcv_constraint.status |= OPA_EI_STATUS_SMASK;
		dd->err_info_rcv_constraint.slid = slid;
		dd->err_info_rcv_constraint.pkey = pkey;
	}
}