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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rvt_qp {int dummy; } ;
struct opa_smp {scalar_t__ mgmt_class; int method; int /*<<< orphan*/  status; } ;
struct hfi1_pportdata {int dummy; } ;
struct TYPE_2__ {int port_cap_flags; } ;
struct hfi1_ibport {TYPE_1__ rvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_MGMT_P_KEY ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_LID_ROUTED ; 
#define  IB_MGMT_METHOD_GET 133 
#define  IB_MGMT_METHOD_GET_RESP 132 
#define  IB_MGMT_METHOD_REPORT 131 
#define  IB_MGMT_METHOD_REPORT_RESP 130 
#define  IB_MGMT_METHOD_SET 129 
 int IB_MGMT_METHOD_TRAP ; 
#define  IB_MGMT_METHOD_TRAP_REPRESS 128 
 int IB_PORT_SM ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_METHOD ; 
 int /*<<< orphan*/  ingress_pkey_table_fail (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 scalar_t__ rcv_pkey_check (struct hfi1_pportdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opa_smp_check(struct hfi1_ibport *ibp, u16 pkey, u8 sc5,
			 struct rvt_qp *qp, u16 slid, struct opa_smp *smp)
{
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	/*
	 * I don't think it's possible for us to get here with sc != 0xf,
	 * but check it to be certain.
	 */
	if (sc5 != 0xf)
		return 1;

	if (rcv_pkey_check(ppd, pkey, sc5, slid))
		return 1;

	/*
	 * At this point we know (and so don't need to check again) that
	 * the pkey is either LIM_MGMT_P_KEY, or FULL_MGMT_P_KEY
	 * (see ingress_pkey_check).
	 */
	if (smp->mgmt_class != IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE &&
	    smp->mgmt_class != IB_MGMT_CLASS_SUBN_LID_ROUTED) {
		ingress_pkey_table_fail(ppd, pkey, slid);
		return 1;
	}

	/*
	 * SMPs fall into one of four (disjoint) categories:
	 * SMA request, SMA response, SMA trap, or SMA trap repress.
	 * Our response depends, in part, on which type of SMP we're
	 * processing.
	 *
	 * If this is an SMA response, skip the check here.
	 *
	 * If this is an SMA request or SMA trap repress:
	 *   - pkey != FULL_MGMT_P_KEY =>
	 *       increment port recv constraint errors, drop MAD
	 *
	 * Otherwise:
	 *    - accept if the port is running an SM
	 *    - drop MAD if it's an SMA trap
	 *    - pkey == FULL_MGMT_P_KEY =>
	 *        reply with unsupported method
	 *    - pkey != FULL_MGMT_P_KEY =>
	 *	  increment port recv constraint errors, drop MAD
	 */
	switch (smp->method) {
	case IB_MGMT_METHOD_GET_RESP:
	case IB_MGMT_METHOD_REPORT_RESP:
		break;
	case IB_MGMT_METHOD_GET:
	case IB_MGMT_METHOD_SET:
	case IB_MGMT_METHOD_REPORT:
	case IB_MGMT_METHOD_TRAP_REPRESS:
		if (pkey != FULL_MGMT_P_KEY) {
			ingress_pkey_table_fail(ppd, pkey, slid);
			return 1;
		}
		break;
	default:
		if (ibp->rvp.port_cap_flags & IB_PORT_SM)
			return 0;
		if (smp->method == IB_MGMT_METHOD_TRAP)
			return 1;
		if (pkey == FULL_MGMT_P_KEY) {
			smp->status |= IB_SMP_UNSUP_METHOD;
			return 0;
		}
		ingress_pkey_table_fail(ppd, pkey, slid);
		return 1;
	}
	return 0;
}