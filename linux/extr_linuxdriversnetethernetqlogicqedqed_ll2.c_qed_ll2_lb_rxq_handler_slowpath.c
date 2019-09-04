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
typedef  int /*<<< orphan*/  u32 ;
struct qed_hwfn {int /*<<< orphan*/  p_ooo_info; } ;
struct ooo_opaque {scalar_t__ ooo_opcode; int /*<<< orphan*/  cid; } ;
struct core_rx_slow_path_cqe {scalar_t__ ramrod_cmd_id; int /*<<< orphan*/  opaque_data; } ;

/* Variables and functions */
 scalar_t__ CORE_RAMROD_RX_QUEUE_FLUSH ; 
 scalar_t__ TCP_EVENT_DELETE_ISLES ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ooo_release_connection_isles (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
qed_ll2_lb_rxq_handler_slowpath(struct qed_hwfn *p_hwfn,
				struct core_rx_slow_path_cqe *p_cqe)
{
	struct ooo_opaque *iscsi_ooo;
	u32 cid;

	if (p_cqe->ramrod_cmd_id != CORE_RAMROD_RX_QUEUE_FLUSH)
		return false;

	iscsi_ooo = (struct ooo_opaque *)&p_cqe->opaque_data;
	if (iscsi_ooo->ooo_opcode != TCP_EVENT_DELETE_ISLES)
		return false;

	/* Need to make a flush */
	cid = le32_to_cpu(iscsi_ooo->cid);
	qed_ooo_release_connection_isles(p_hwfn, p_hwfn->p_ooo_info, cid);

	return true;
}