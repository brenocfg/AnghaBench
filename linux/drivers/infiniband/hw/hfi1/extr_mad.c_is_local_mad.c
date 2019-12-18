#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dr_slid; scalar_t__ dr_dlid; } ;
struct TYPE_3__ {TYPE_2__ dr; } ;
struct opa_smp {scalar_t__ mgmt_class; scalar_t__ hop_cnt; TYPE_1__ route; } ;
struct opa_mad {int dummy; } ;
struct ib_wc {scalar_t__ slid; } ;
struct hfi1_pportdata {scalar_t__ lid; } ;
struct hfi1_ibport {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 scalar_t__ OPA_LID_PERMISSIVE ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 

__attribute__((used)) static int is_local_mad(struct hfi1_ibport *ibp, const struct opa_mad *mad,
			const struct ib_wc *in_wc)
{
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	const struct opa_smp *smp = (const struct opa_smp *)mad;

	if (smp->mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE) {
		return (smp->hop_cnt == 0 &&
			smp->route.dr.dr_slid == OPA_LID_PERMISSIVE &&
			smp->route.dr.dr_dlid == OPA_LID_PERMISSIVE);
	}

	return (in_wc->slid == ppd->lid);
}