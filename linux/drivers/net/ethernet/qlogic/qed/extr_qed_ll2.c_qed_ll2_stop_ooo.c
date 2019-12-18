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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  ll2_ooo_queue_id; } ;
struct TYPE_4__ {TYPE_1__ iscsi_pf_params; } ;
struct qed_hwfn {TYPE_2__ pf_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_LL2_UNUSED_HANDLE ; 
 int QED_MSG_LL2 ; 
 int QED_MSG_STORAGE ; 
 int /*<<< orphan*/  qed_ll2_release_connection (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ll2_terminate_connection (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_ll2_stop_ooo(struct qed_hwfn *p_hwfn)
{
	u8 *handle = &p_hwfn->pf_params.iscsi_pf_params.ll2_ooo_queue_id;

	DP_VERBOSE(p_hwfn, (QED_MSG_STORAGE | QED_MSG_LL2),
		   "Stopping LL2 OOO queue [%02x]\n", *handle);

	qed_ll2_terminate_connection(p_hwfn, *handle);
	qed_ll2_release_connection(p_hwfn, *handle);
	*handle = QED_LL2_UNUSED_HANDLE;
}