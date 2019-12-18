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
typedef  scalar_t__ u16 ;
struct ib_wc {size_t pkey_index; int /*<<< orphan*/  slid; } ;
struct hfi1_pportdata {scalar_t__* pkeys; } ;
struct hfi1_ibport {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ FULL_MGMT_P_KEY ; 
 scalar_t__ LIM_MGMT_P_KEY ; 
 int /*<<< orphan*/  ingress_pkey_table_fail (struct hfi1_pportdata*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 

__attribute__((used)) static int opa_local_smp_check(struct hfi1_ibport *ibp,
			       const struct ib_wc *in_wc)
{
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u16 pkey;

	if (in_wc->pkey_index >= ARRAY_SIZE(ppd->pkeys))
		return 1;

	pkey = ppd->pkeys[in_wc->pkey_index];
	/*
	 * We need to do the "node-local" checks specified in OPAv1,
	 * rev 0.90, section 9.10.26, which are:
	 *   - pkey is 0x7fff, or 0xffff
	 *   - Source QPN == 0 || Destination QPN == 0
	 *   - the MAD header's management class is either
	 *     IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE or
	 *     IB_MGMT_CLASS_SUBN_LID_ROUTED
	 *   - SLID != 0
	 *
	 * However, we know (and so don't need to check again) that,
	 * for local SMPs, the MAD stack passes MADs with:
	 *   - Source QPN of 0
	 *   - MAD mgmt_class is IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE
	 *   - SLID is either: OPA_LID_PERMISSIVE (0xFFFFFFFF), or
	 *     our own port's lid
	 *
	 */
	if (pkey == LIM_MGMT_P_KEY || pkey == FULL_MGMT_P_KEY)
		return 0;
	ingress_pkey_table_fail(ppd, pkey, in_wc->slid);
	return 1;
}