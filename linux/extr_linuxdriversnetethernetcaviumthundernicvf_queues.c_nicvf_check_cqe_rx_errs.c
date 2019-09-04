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
struct nicvf {TYPE_1__* drv_stats; int /*<<< orphan*/  netdev; } ;
struct cqe_rx_t {int err_opcode; int /*<<< orphan*/  err_level; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_truncated_pkts; int /*<<< orphan*/  rx_l4_pclp; int /*<<< orphan*/  rx_tcp_offset_errs; int /*<<< orphan*/  rx_tcp_flag_errs; int /*<<< orphan*/  rx_l4_port_errs; int /*<<< orphan*/  rx_udp_len_errs; int /*<<< orphan*/  rx_l4_csum_errs; int /*<<< orphan*/  rx_l4_malformed; int /*<<< orphan*/  rx_l3_pclp; int /*<<< orphan*/  rx_ip_ttl_errs; int /*<<< orphan*/  rx_ip_payload_malformed; int /*<<< orphan*/  rx_ip_hdr_malformed; int /*<<< orphan*/  rx_ip_csum_errs; int /*<<< orphan*/  rx_ip_ver_errs; int /*<<< orphan*/  rx_l2_pclp; int /*<<< orphan*/  rx_l2_len_mismatch; int /*<<< orphan*/  rx_undersize; int /*<<< orphan*/  rx_oversize; int /*<<< orphan*/  rx_l2_hdr_malformed; int /*<<< orphan*/  rx_prel2_errs; int /*<<< orphan*/  rx_bgx_errs; int /*<<< orphan*/  rx_fcs_errs; int /*<<< orphan*/  rx_jabber_errs; int /*<<< orphan*/  rx_bgx_truncated_pkts; } ;

/* Variables and functions */
#define  CQ_RX_ERROP_IP_CSUM_ERR 151 
#define  CQ_RX_ERROP_IP_HOP 150 
#define  CQ_RX_ERROP_IP_MAL 149 
#define  CQ_RX_ERROP_IP_MALD 148 
#define  CQ_RX_ERROP_IP_NOT 147 
#define  CQ_RX_ERROP_L2_LENMISM 146 
#define  CQ_RX_ERROP_L2_MAL 145 
#define  CQ_RX_ERROP_L2_OVERSIZE 144 
#define  CQ_RX_ERROP_L2_PCLP 143 
#define  CQ_RX_ERROP_L2_UNDERSIZE 142 
#define  CQ_RX_ERROP_L3_PCLP 141 
#define  CQ_RX_ERROP_L4_CHK 140 
#define  CQ_RX_ERROP_L4_MAL 139 
#define  CQ_RX_ERROP_L4_PCLP 138 
#define  CQ_RX_ERROP_L4_PORT 137 
#define  CQ_RX_ERROP_PREL2_ERR 136 
#define  CQ_RX_ERROP_RBDR_TRUNC 135 
#define  CQ_RX_ERROP_RE_FCS 134 
#define  CQ_RX_ERROP_RE_JABBER 133 
#define  CQ_RX_ERROP_RE_PARTIAL 132 
#define  CQ_RX_ERROP_RE_RX_CTL 131 
#define  CQ_RX_ERROP_TCP_FLAG 130 
#define  CQ_RX_ERROP_TCP_OFFSET 129 
#define  CQ_RX_ERROP_UDP_LEN 128 
 int /*<<< orphan*/  netif_err (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

int nicvf_check_cqe_rx_errs(struct nicvf *nic, struct cqe_rx_t *cqe_rx)
{
	netif_err(nic, rx_err, nic->netdev,
		  "RX error CQE err_level 0x%x err_opcode 0x%x\n",
		  cqe_rx->err_level, cqe_rx->err_opcode);

	switch (cqe_rx->err_opcode) {
	case CQ_RX_ERROP_RE_PARTIAL:
		this_cpu_inc(nic->drv_stats->rx_bgx_truncated_pkts);
		break;
	case CQ_RX_ERROP_RE_JABBER:
		this_cpu_inc(nic->drv_stats->rx_jabber_errs);
		break;
	case CQ_RX_ERROP_RE_FCS:
		this_cpu_inc(nic->drv_stats->rx_fcs_errs);
		break;
	case CQ_RX_ERROP_RE_RX_CTL:
		this_cpu_inc(nic->drv_stats->rx_bgx_errs);
		break;
	case CQ_RX_ERROP_PREL2_ERR:
		this_cpu_inc(nic->drv_stats->rx_prel2_errs);
		break;
	case CQ_RX_ERROP_L2_MAL:
		this_cpu_inc(nic->drv_stats->rx_l2_hdr_malformed);
		break;
	case CQ_RX_ERROP_L2_OVERSIZE:
		this_cpu_inc(nic->drv_stats->rx_oversize);
		break;
	case CQ_RX_ERROP_L2_UNDERSIZE:
		this_cpu_inc(nic->drv_stats->rx_undersize);
		break;
	case CQ_RX_ERROP_L2_LENMISM:
		this_cpu_inc(nic->drv_stats->rx_l2_len_mismatch);
		break;
	case CQ_RX_ERROP_L2_PCLP:
		this_cpu_inc(nic->drv_stats->rx_l2_pclp);
		break;
	case CQ_RX_ERROP_IP_NOT:
		this_cpu_inc(nic->drv_stats->rx_ip_ver_errs);
		break;
	case CQ_RX_ERROP_IP_CSUM_ERR:
		this_cpu_inc(nic->drv_stats->rx_ip_csum_errs);
		break;
	case CQ_RX_ERROP_IP_MAL:
		this_cpu_inc(nic->drv_stats->rx_ip_hdr_malformed);
		break;
	case CQ_RX_ERROP_IP_MALD:
		this_cpu_inc(nic->drv_stats->rx_ip_payload_malformed);
		break;
	case CQ_RX_ERROP_IP_HOP:
		this_cpu_inc(nic->drv_stats->rx_ip_ttl_errs);
		break;
	case CQ_RX_ERROP_L3_PCLP:
		this_cpu_inc(nic->drv_stats->rx_l3_pclp);
		break;
	case CQ_RX_ERROP_L4_MAL:
		this_cpu_inc(nic->drv_stats->rx_l4_malformed);
		break;
	case CQ_RX_ERROP_L4_CHK:
		this_cpu_inc(nic->drv_stats->rx_l4_csum_errs);
		break;
	case CQ_RX_ERROP_UDP_LEN:
		this_cpu_inc(nic->drv_stats->rx_udp_len_errs);
		break;
	case CQ_RX_ERROP_L4_PORT:
		this_cpu_inc(nic->drv_stats->rx_l4_port_errs);
		break;
	case CQ_RX_ERROP_TCP_FLAG:
		this_cpu_inc(nic->drv_stats->rx_tcp_flag_errs);
		break;
	case CQ_RX_ERROP_TCP_OFFSET:
		this_cpu_inc(nic->drv_stats->rx_tcp_offset_errs);
		break;
	case CQ_RX_ERROP_L4_PCLP:
		this_cpu_inc(nic->drv_stats->rx_l4_pclp);
		break;
	case CQ_RX_ERROP_RBDR_TRUNC:
		this_cpu_inc(nic->drv_stats->rx_truncated_pkts);
		break;
	}

	return 1;
}