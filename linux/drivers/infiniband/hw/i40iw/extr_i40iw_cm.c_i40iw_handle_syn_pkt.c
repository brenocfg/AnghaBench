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
typedef  int /*<<< orphan*/  u32 ;
struct tcphdr {int doff; int /*<<< orphan*/  seq; } ;
struct i40iw_puda_buf {scalar_t__ tcph; } ;
struct TYPE_5__ {int /*<<< orphan*/  rcv_nxt; } ;
struct i40iw_cm_node {int state; int accept_pend; int qhash_set; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  iwdev; TYPE_3__* listener; TYPE_2__ tcp_cntxt; TYPE_1__* cm_core; } ;
struct i40iw_cm_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pend_accepts_cnt; int /*<<< orphan*/  backlog; } ;
struct TYPE_4__ {int /*<<< orphan*/  stats_backlog_drops; } ;

/* Variables and functions */
#define  I40IW_CM_STATE_CLOSED 139 
#define  I40IW_CM_STATE_CLOSING 138 
#define  I40IW_CM_STATE_ESTABLISHED 137 
#define  I40IW_CM_STATE_FIN_WAIT1 136 
#define  I40IW_CM_STATE_FIN_WAIT2 135 
#define  I40IW_CM_STATE_LAST_ACK 134 
#define  I40IW_CM_STATE_LISTENING 133 
#define  I40IW_CM_STATE_MPAREQ_RCVD 132 
#define  I40IW_CM_STATE_MPAREQ_SENT 131 
#define  I40IW_CM_STATE_OFFLOADED 130 
 int I40IW_CM_STATE_SYN_RCVD ; 
#define  I40IW_CM_STATE_SYN_SENT 129 
#define  I40IW_CM_STATE_UNKNOWN 128 
 int /*<<< orphan*/  I40IW_QHASH_MANAGE_TYPE_ADD ; 
 int /*<<< orphan*/  I40IW_QHASH_TYPE_TCP_ESTABLISHED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_active_open_err (struct i40iw_cm_node*,int) ; 
 int /*<<< orphan*/  i40iw_cleanup_retrans_entry (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  i40iw_get_addr_info (struct i40iw_cm_node*,struct i40iw_cm_info*) ; 
 int i40iw_handle_tcp_options (struct i40iw_cm_node*,struct tcphdr*,int,int) ; 
 int i40iw_manage_qhash (int /*<<< orphan*/ ,struct i40iw_cm_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  i40iw_passive_open_err (struct i40iw_cm_node*,int) ; 
 int /*<<< orphan*/  i40iw_send_reset (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40iw_handle_syn_pkt(struct i40iw_cm_node *cm_node,
				 struct i40iw_puda_buf *rbuf)
{
	struct tcphdr *tcph = (struct tcphdr *)rbuf->tcph;
	int ret;
	u32 inc_sequence;
	int optionsize;
	struct i40iw_cm_info nfo;

	optionsize = (tcph->doff << 2) - sizeof(struct tcphdr);
	inc_sequence = ntohl(tcph->seq);

	switch (cm_node->state) {
	case I40IW_CM_STATE_SYN_SENT:
	case I40IW_CM_STATE_MPAREQ_SENT:
		/* Rcvd syn on active open connection */
		i40iw_active_open_err(cm_node, 1);
		break;
	case I40IW_CM_STATE_LISTENING:
		/* Passive OPEN */
		if (atomic_read(&cm_node->listener->pend_accepts_cnt) >
		    cm_node->listener->backlog) {
			cm_node->cm_core->stats_backlog_drops++;
			i40iw_passive_open_err(cm_node, false);
			break;
		}
		ret = i40iw_handle_tcp_options(cm_node, tcph, optionsize, 1);
		if (ret) {
			i40iw_passive_open_err(cm_node, false);
			/* drop pkt */
			break;
		}
		cm_node->tcp_cntxt.rcv_nxt = inc_sequence + 1;
		cm_node->accept_pend = 1;
		atomic_inc(&cm_node->listener->pend_accepts_cnt);

		cm_node->state = I40IW_CM_STATE_SYN_RCVD;
		i40iw_get_addr_info(cm_node, &nfo);
		ret = i40iw_manage_qhash(cm_node->iwdev,
					 &nfo,
					 I40IW_QHASH_TYPE_TCP_ESTABLISHED,
					 I40IW_QHASH_MANAGE_TYPE_ADD,
					 (void *)cm_node,
					 false);
		cm_node->qhash_set = true;
		break;
	case I40IW_CM_STATE_CLOSED:
		i40iw_cleanup_retrans_entry(cm_node);
		atomic_inc(&cm_node->ref_count);
		i40iw_send_reset(cm_node);
		break;
	case I40IW_CM_STATE_OFFLOADED:
	case I40IW_CM_STATE_ESTABLISHED:
	case I40IW_CM_STATE_FIN_WAIT1:
	case I40IW_CM_STATE_FIN_WAIT2:
	case I40IW_CM_STATE_MPAREQ_RCVD:
	case I40IW_CM_STATE_LAST_ACK:
	case I40IW_CM_STATE_CLOSING:
	case I40IW_CM_STATE_UNKNOWN:
	default:
		break;
	}
}