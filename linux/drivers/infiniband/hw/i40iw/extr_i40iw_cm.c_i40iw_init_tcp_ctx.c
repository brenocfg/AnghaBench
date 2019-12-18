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
typedef  int u16 ;
struct i40iw_tcp_offload_info {int drop_ooo_seg; int wscale; int ignore_tcp_opt; int ignore_tcp_uns_opt; int no_nagle; int rcv_wscale; int insert_vlan_tag; void* dest_ip_addr0; void* arp_idx; void* local_ipaddr3; void* local_ipaddr2; void* local_ipaddr1; void* local_ipaddr0; void* dest_ip_addr3; void* dest_ip_addr2; void* dest_ip_addr1; void* dst_port; void* src_port; void* vlan_tag; void* snd_mss; scalar_t__ flow_label; void* rcv_wnd; void* max_snd_window; void* snd_wl2; void* snd_wl1; void* cwnd; void* snd_una; void* snd_max; void* rcv_nxt; void* snd_wnd; void* snd_nxt; int /*<<< orphan*/  snd_wscale; int /*<<< orphan*/  tcp_state; int /*<<< orphan*/  rexmit_thresh; void* ss_thresh; void* rtt_var; int /*<<< orphan*/  ttl; scalar_t__ ipv4; } ;
struct i40iw_qp {int /*<<< orphan*/  iwdev; } ;
struct TYPE_2__ {int rcv_wscale; int loc_seq_num; int snd_wnd; int rcv_nxt; int mss; int max_snd_wnd; int rcv_wnd; int /*<<< orphan*/  snd_wscale; } ;
struct i40iw_cm_node {int vlan_id; int loc_port; int rem_port; int* rem_addr; int* loc_addr; scalar_t__ ipv4; scalar_t__ user_pri; TYPE_1__ tcp_cntxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_ARP_RESOLVE ; 
 int /*<<< orphan*/  I40IW_DEFAULT_REXMIT_THRESH ; 
 int I40IW_DEFAULT_RTT_VAR ; 
 int I40IW_DEFAULT_SS_THRESH ; 
 int /*<<< orphan*/  I40IW_DEFAULT_TTL ; 
 int /*<<< orphan*/  I40IW_TCP_STATE_ESTABLISHED ; 
 int I40IW_VLAN_PRIO_SHIFT ; 
 int VLAN_VID_MASK ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ i40iw_arp_table (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40iw_init_tcp_ctx(struct i40iw_cm_node *cm_node,
			       struct i40iw_tcp_offload_info *tcp_info,
			       struct i40iw_qp *iwqp)
{
	tcp_info->ipv4 = cm_node->ipv4;
	tcp_info->drop_ooo_seg = true;
	tcp_info->wscale = true;
	tcp_info->ignore_tcp_opt = true;
	tcp_info->ignore_tcp_uns_opt = true;
	tcp_info->no_nagle = false;

	tcp_info->ttl = I40IW_DEFAULT_TTL;
	tcp_info->rtt_var = cpu_to_le32(I40IW_DEFAULT_RTT_VAR);
	tcp_info->ss_thresh = cpu_to_le32(I40IW_DEFAULT_SS_THRESH);
	tcp_info->rexmit_thresh = I40IW_DEFAULT_REXMIT_THRESH;

	tcp_info->tcp_state = I40IW_TCP_STATE_ESTABLISHED;
	tcp_info->snd_wscale = cm_node->tcp_cntxt.snd_wscale;
	tcp_info->rcv_wscale = cm_node->tcp_cntxt.rcv_wscale;

	tcp_info->snd_nxt = cpu_to_le32(cm_node->tcp_cntxt.loc_seq_num);
	tcp_info->snd_wnd = cpu_to_le32(cm_node->tcp_cntxt.snd_wnd);
	tcp_info->rcv_nxt = cpu_to_le32(cm_node->tcp_cntxt.rcv_nxt);
	tcp_info->snd_max = cpu_to_le32(cm_node->tcp_cntxt.loc_seq_num);

	tcp_info->snd_una = cpu_to_le32(cm_node->tcp_cntxt.loc_seq_num);
	tcp_info->cwnd = cpu_to_le32(2 * cm_node->tcp_cntxt.mss);
	tcp_info->snd_wl1 = cpu_to_le32(cm_node->tcp_cntxt.rcv_nxt);
	tcp_info->snd_wl2 = cpu_to_le32(cm_node->tcp_cntxt.loc_seq_num);
	tcp_info->max_snd_window = cpu_to_le32(cm_node->tcp_cntxt.max_snd_wnd);
	tcp_info->rcv_wnd = cpu_to_le32(cm_node->tcp_cntxt.rcv_wnd <<
					cm_node->tcp_cntxt.rcv_wscale);

	tcp_info->flow_label = 0;
	tcp_info->snd_mss = cpu_to_le32(((u32)cm_node->tcp_cntxt.mss));
	if (cm_node->vlan_id <= VLAN_VID_MASK) {
		tcp_info->insert_vlan_tag = true;
		tcp_info->vlan_tag = cpu_to_le16(((u16)cm_node->user_pri << I40IW_VLAN_PRIO_SHIFT) |
						  cm_node->vlan_id);
	}
	if (cm_node->ipv4) {
		tcp_info->src_port = cpu_to_le16(cm_node->loc_port);
		tcp_info->dst_port = cpu_to_le16(cm_node->rem_port);

		tcp_info->dest_ip_addr3 = cpu_to_le32(cm_node->rem_addr[0]);
		tcp_info->local_ipaddr3 = cpu_to_le32(cm_node->loc_addr[0]);
		tcp_info->arp_idx =
			cpu_to_le16((u16)i40iw_arp_table(
							 iwqp->iwdev,
							 &tcp_info->dest_ip_addr3,
							 true,
							 NULL,
							 I40IW_ARP_RESOLVE));
	} else {
		tcp_info->src_port = cpu_to_le16(cm_node->loc_port);
		tcp_info->dst_port = cpu_to_le16(cm_node->rem_port);
		tcp_info->dest_ip_addr0 = cpu_to_le32(cm_node->rem_addr[0]);
		tcp_info->dest_ip_addr1 = cpu_to_le32(cm_node->rem_addr[1]);
		tcp_info->dest_ip_addr2 = cpu_to_le32(cm_node->rem_addr[2]);
		tcp_info->dest_ip_addr3 = cpu_to_le32(cm_node->rem_addr[3]);
		tcp_info->local_ipaddr0 = cpu_to_le32(cm_node->loc_addr[0]);
		tcp_info->local_ipaddr1 = cpu_to_le32(cm_node->loc_addr[1]);
		tcp_info->local_ipaddr2 = cpu_to_le32(cm_node->loc_addr[2]);
		tcp_info->local_ipaddr3 = cpu_to_le32(cm_node->loc_addr[3]);
		tcp_info->arp_idx =
			cpu_to_le16((u16)i40iw_arp_table(
							 iwqp->iwdev,
							 &tcp_info->dest_ip_addr0,
							 false,
							 NULL,
							 I40IW_ARP_RESOLVE));
	}
}