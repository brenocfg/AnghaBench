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
struct TYPE_2__ {scalar_t__ conn_type; } ;
struct qed_ll2_info {TYPE_1__ input; } ;
struct qed_hwfn {int /*<<< orphan*/  p_ooo_info; } ;

/* Variables and functions */
 scalar_t__ QED_LL2_TYPE_OOO ; 
 int /*<<< orphan*/  qed_ooo_release_all_isles (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ooo_submit_rx_buffers (struct qed_hwfn*,struct qed_ll2_info*) ; 

__attribute__((used)) static void
qed_ll2_establish_connection_ooo(struct qed_hwfn *p_hwfn,
				 struct qed_ll2_info *p_ll2_conn)
{
	if (p_ll2_conn->input.conn_type != QED_LL2_TYPE_OOO)
		return;

	qed_ooo_release_all_isles(p_hwfn, p_hwfn->p_ooo_info);
	qed_ooo_submit_rx_buffers(p_hwfn, p_ll2_conn);
}