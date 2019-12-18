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
typedef  int u32 ;
struct tcphdr {scalar_t__ fin; scalar_t__ ack; scalar_t__ syn; scalar_t__ rst; } ;
struct i40iw_puda_buf {scalar_t__ tcph; } ;
struct i40iw_cm_node {int dummy; } ;
typedef  enum i40iw_tcpip_pkt_type { ____Placeholder_i40iw_tcpip_pkt_type } i40iw_tcpip_pkt_type ;

/* Variables and functions */
#define  I40IW_PKT_TYPE_ACK 131 
#define  I40IW_PKT_TYPE_RST 130 
#define  I40IW_PKT_TYPE_SYN 129 
#define  I40IW_PKT_TYPE_SYNACK 128 
 int I40IW_PKT_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  i40iw_check_seq (struct i40iw_cm_node*,struct tcphdr*) ; 
 int i40iw_handle_ack_pkt (struct i40iw_cm_node*,struct i40iw_puda_buf*) ; 
 int /*<<< orphan*/  i40iw_handle_fin_pkt (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  i40iw_handle_rst_pkt (struct i40iw_cm_node*,struct i40iw_puda_buf*) ; 
 int /*<<< orphan*/  i40iw_handle_syn_pkt (struct i40iw_cm_node*,struct i40iw_puda_buf*) ; 
 int /*<<< orphan*/  i40iw_handle_synack_pkt (struct i40iw_cm_node*,struct i40iw_puda_buf*) ; 

__attribute__((used)) static void i40iw_process_packet(struct i40iw_cm_node *cm_node,
				 struct i40iw_puda_buf *rbuf)
{
	enum i40iw_tcpip_pkt_type pkt_type = I40IW_PKT_TYPE_UNKNOWN;
	struct tcphdr *tcph = (struct tcphdr *)rbuf->tcph;
	u32 fin_set = 0;
	int ret;

	if (tcph->rst) {
		pkt_type = I40IW_PKT_TYPE_RST;
	} else if (tcph->syn) {
		pkt_type = I40IW_PKT_TYPE_SYN;
		if (tcph->ack)
			pkt_type = I40IW_PKT_TYPE_SYNACK;
	} else if (tcph->ack) {
		pkt_type = I40IW_PKT_TYPE_ACK;
	}
	if (tcph->fin)
		fin_set = 1;

	switch (pkt_type) {
	case I40IW_PKT_TYPE_SYN:
		i40iw_handle_syn_pkt(cm_node, rbuf);
		break;
	case I40IW_PKT_TYPE_SYNACK:
		i40iw_handle_synack_pkt(cm_node, rbuf);
		break;
	case I40IW_PKT_TYPE_ACK:
		ret = i40iw_handle_ack_pkt(cm_node, rbuf);
		if (fin_set && !ret)
			i40iw_handle_fin_pkt(cm_node);
		break;
	case I40IW_PKT_TYPE_RST:
		i40iw_handle_rst_pkt(cm_node, rbuf);
		break;
	default:
		if (fin_set &&
		    (!i40iw_check_seq(cm_node, (struct tcphdr *)rbuf->tcph)))
			i40iw_handle_fin_pkt(cm_node);
		break;
	}
}