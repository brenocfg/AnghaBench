#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ is_target; } ;
struct TYPE_6__ {TYPE_2__ fcoe_pf_params; } ;
struct TYPE_4__ {scalar_t__ personality; } ;
struct qed_hwfn {TYPE_3__ pf_params; TYPE_1__ hw_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRS_REG_SEARCH_RESP_INITIATOR_TYPE_RT_OFFSET ; 
 scalar_t__ QED_PCI_FCOE ; 
 int /*<<< orphan*/  STORE_RT_REG (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_prs_init_common(struct qed_hwfn *p_hwfn)
{
	if ((p_hwfn->hw_info.personality == QED_PCI_FCOE) &&
	    p_hwfn->pf_params.fcoe_pf_params.is_target)
		STORE_RT_REG(p_hwfn,
			     PRS_REG_SEARCH_RESP_INITIATOR_TYPE_RT_OFFSET, 0);
}