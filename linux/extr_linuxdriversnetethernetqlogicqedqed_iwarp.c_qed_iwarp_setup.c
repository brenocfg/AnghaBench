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
typedef  int u32 ;
struct qed_rdma_start_in_params {int dummy; } ;
struct qed_ptt {int dummy; } ;
struct qed_iwarp_info {int rcv_wnd_scale; int rcv_wnd_size; int rtr_type; int /*<<< orphan*/  listen_list; int /*<<< orphan*/  ep_list; int /*<<< orphan*/  qp_lock; int /*<<< orphan*/  peer2peer; int /*<<< orphan*/  mpa_rev; int /*<<< orphan*/  crc_needed; int /*<<< orphan*/  tcp_flags; } ;
struct qed_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {struct qed_iwarp_info iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MPA_NEGOTIATION_TYPE_ENHANCED ; 
 int MPA_RTR_TYPE_ZERO_READ ; 
 int MPA_RTR_TYPE_ZERO_SEND ; 
 int MPA_RTR_TYPE_ZERO_WRITE ; 
 int /*<<< orphan*/  PROTOCOLID_IWARP ; 
 int /*<<< orphan*/  QED_IWARP_PARAM_CRC_NEEDED ; 
 int /*<<< orphan*/  QED_IWARP_PARAM_P2P ; 
 int QED_IWARP_RCV_WND_SIZE_DEF ; 
 int QED_IWARP_RCV_WND_SIZE_MIN ; 
 int /*<<< orphan*/  QED_IWARP_TS_EN ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  qed_iwarp_async_event ; 
 int qed_iwarp_ll2_start (struct qed_hwfn*,struct qed_rdma_start_in_params*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_ooo_setup (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_spq_register_async_cb (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int qed_iwarp_setup(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt,
		    struct qed_rdma_start_in_params *params)
{
	struct qed_iwarp_info *iwarp_info;
	u32 rcv_wnd_size;

	iwarp_info = &p_hwfn->p_rdma_info->iwarp;

	iwarp_info->tcp_flags = QED_IWARP_TS_EN;
	rcv_wnd_size = QED_IWARP_RCV_WND_SIZE_DEF;

	/* value 0 is used for ilog2(QED_IWARP_RCV_WND_SIZE_MIN) */
	iwarp_info->rcv_wnd_scale = ilog2(rcv_wnd_size) -
	    ilog2(QED_IWARP_RCV_WND_SIZE_MIN);
	iwarp_info->rcv_wnd_size = rcv_wnd_size >> iwarp_info->rcv_wnd_scale;
	iwarp_info->crc_needed = QED_IWARP_PARAM_CRC_NEEDED;
	iwarp_info->mpa_rev = MPA_NEGOTIATION_TYPE_ENHANCED;

	iwarp_info->peer2peer = QED_IWARP_PARAM_P2P;

	iwarp_info->rtr_type =  MPA_RTR_TYPE_ZERO_SEND |
				MPA_RTR_TYPE_ZERO_WRITE |
				MPA_RTR_TYPE_ZERO_READ;

	spin_lock_init(&p_hwfn->p_rdma_info->iwarp.qp_lock);
	INIT_LIST_HEAD(&p_hwfn->p_rdma_info->iwarp.ep_list);
	INIT_LIST_HEAD(&p_hwfn->p_rdma_info->iwarp.listen_list);

	qed_spq_register_async_cb(p_hwfn, PROTOCOLID_IWARP,
				  qed_iwarp_async_event);
	qed_ooo_setup(p_hwfn);

	return qed_iwarp_ll2_start(p_hwfn, params, p_ptt);
}