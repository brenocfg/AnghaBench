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
struct qed_hwfn {int dummy; } ;
struct TYPE_2__ {scalar_t__ ip_version; int /*<<< orphan*/  syn_phy_addr_hi; int /*<<< orphan*/  syn_phy_addr_lo; int /*<<< orphan*/  syn_ip_payload_length; int /*<<< orphan*/  flags; int /*<<< orphan*/  connect_mode; int /*<<< orphan*/  rcv_wnd_scale; int /*<<< orphan*/  mss; int /*<<< orphan*/  tos_or_tc; int /*<<< orphan*/  ttl; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  remote_ip; int /*<<< orphan*/  local_port; int /*<<< orphan*/  local_ip; int /*<<< orphan*/  remote_mac_addr_hi; int /*<<< orphan*/  remote_mac_addr_mid; int /*<<< orphan*/  remote_mac_addr_lo; int /*<<< orphan*/  local_mac_addr_hi; int /*<<< orphan*/  local_mac_addr_mid; int /*<<< orphan*/  local_mac_addr_lo; } ;
struct iwarp_tcp_offload_ramrod_data {TYPE_1__ tcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 scalar_t__ TCP_IPV4 ; 

__attribute__((used)) static void
qed_iwarp_print_tcp_ramrod(struct qed_hwfn *p_hwfn,
			   struct iwarp_tcp_offload_ramrod_data *p_tcp_ramrod)
{
	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "local_mac=%x %x %x, remote_mac=%x %x %x\n",
		   p_tcp_ramrod->tcp.local_mac_addr_lo,
		   p_tcp_ramrod->tcp.local_mac_addr_mid,
		   p_tcp_ramrod->tcp.local_mac_addr_hi,
		   p_tcp_ramrod->tcp.remote_mac_addr_lo,
		   p_tcp_ramrod->tcp.remote_mac_addr_mid,
		   p_tcp_ramrod->tcp.remote_mac_addr_hi);

	if (p_tcp_ramrod->tcp.ip_version == TCP_IPV4) {
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "local_ip=%pI4h:%x, remote_ip=%pI4h:%x, vlan=%x\n",
			   p_tcp_ramrod->tcp.local_ip,
			   p_tcp_ramrod->tcp.local_port,
			   p_tcp_ramrod->tcp.remote_ip,
			   p_tcp_ramrod->tcp.remote_port,
			   p_tcp_ramrod->tcp.vlan_id);
	} else {
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "local_ip=%pI6:%x, remote_ip=%pI6:%x, vlan=%x\n",
			   p_tcp_ramrod->tcp.local_ip,
			   p_tcp_ramrod->tcp.local_port,
			   p_tcp_ramrod->tcp.remote_ip,
			   p_tcp_ramrod->tcp.remote_port,
			   p_tcp_ramrod->tcp.vlan_id);
	}

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
		   "flow_label=%x, ttl=%x, tos_or_tc=%x, mss=%x, rcv_wnd_scale=%x, connect_mode=%x, flags=%x\n",
		   p_tcp_ramrod->tcp.flow_label,
		   p_tcp_ramrod->tcp.ttl,
		   p_tcp_ramrod->tcp.tos_or_tc,
		   p_tcp_ramrod->tcp.mss,
		   p_tcp_ramrod->tcp.rcv_wnd_scale,
		   p_tcp_ramrod->tcp.connect_mode,
		   p_tcp_ramrod->tcp.flags);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "syn_ip_payload_length=%x, lo=%x, hi=%x\n",
		   p_tcp_ramrod->tcp.syn_ip_payload_length,
		   p_tcp_ramrod->tcp.syn_phy_addr_lo,
		   p_tcp_ramrod->tcp.syn_phy_addr_hi);
}