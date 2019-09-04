#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qed_hwfn {TYPE_3__* p_rdma_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_fin_rt; } ;
struct TYPE_5__ {scalar_t__ ll2_ooo_q_index; } ;
struct iwarp_init_func_ramrod_data {TYPE_4__ tcp; TYPE_1__ iwarp; } ;
struct TYPE_6__ {scalar_t__ ll2_ooo_handle; } ;
struct TYPE_7__ {TYPE_2__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  QED_IWARP_MAX_FIN_RT_DEFAULT ; 
 int /*<<< orphan*/  QED_LL2_QUEUE ; 
 scalar_t__ RESC_START (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

void
qed_iwarp_init_fw_ramrod(struct qed_hwfn *p_hwfn,
			 struct iwarp_init_func_ramrod_data *p_ramrod)
{
	p_ramrod->iwarp.ll2_ooo_q_index =
		RESC_START(p_hwfn, QED_LL2_QUEUE) +
		p_hwfn->p_rdma_info->iwarp.ll2_ooo_handle;

	p_ramrod->tcp.max_fin_rt = QED_IWARP_MAX_FIN_RT_DEFAULT;

	return;
}