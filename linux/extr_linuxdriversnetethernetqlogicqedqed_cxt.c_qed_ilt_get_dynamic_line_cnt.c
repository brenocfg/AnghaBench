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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
struct qed_ilt_client_cfg {TYPE_1__ p_size; } ;
struct qed_hwfn {TYPE_3__* p_cxt_mngr; } ;
typedef  enum ilt_clients { ____Placeholder_ilt_clients } ilt_clients ;
struct TYPE_6__ {struct qed_ilt_client_cfg* clients; TYPE_2__* conn_cfg; } ;
struct TYPE_5__ {int cid_count; } ;

/* Variables and functions */
 scalar_t__ CONN_CXT_SIZE (struct qed_hwfn*) ; 
 int ILT_CLI_CDUC ; 
 int ILT_PAGE_IN_BYTES (int /*<<< orphan*/ ) ; 
 size_t PROTOCOLID_ROCE ; 

__attribute__((used)) static u32 qed_ilt_get_dynamic_line_cnt(struct qed_hwfn *p_hwfn,
					enum ilt_clients ilt_client)
{
	u32 cid_count = p_hwfn->p_cxt_mngr->conn_cfg[PROTOCOLID_ROCE].cid_count;
	struct qed_ilt_client_cfg *p_cli;
	u32 lines_to_skip = 0;
	u32 cxts_per_p;

	if (ilt_client == ILT_CLI_CDUC) {
		p_cli = &p_hwfn->p_cxt_mngr->clients[ILT_CLI_CDUC];

		cxts_per_p = ILT_PAGE_IN_BYTES(p_cli->p_size.val) /
		    (u32) CONN_CXT_SIZE(p_hwfn);

		lines_to_skip = cid_count / cxts_per_p;
	}

	return lines_to_skip;
}