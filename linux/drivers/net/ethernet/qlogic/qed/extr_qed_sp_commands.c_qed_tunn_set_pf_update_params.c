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
struct qed_tunnel_info {int /*<<< orphan*/  b_update_rx_cls; int /*<<< orphan*/  ip_gre; int /*<<< orphan*/  l2_gre; int /*<<< orphan*/  ip_geneve; int /*<<< orphan*/  geneve_port; int /*<<< orphan*/  l2_geneve; int /*<<< orphan*/  vxlan_port; int /*<<< orphan*/  vxlan; } ;
struct qed_hwfn {TYPE_1__* cdev; } ;
struct pf_update_tunnel_config {int /*<<< orphan*/  update_rx_pf_clss; int /*<<< orphan*/  tunnel_clss_ipgre; int /*<<< orphan*/  tunnel_clss_l2gre; int /*<<< orphan*/  tunnel_clss_ipgeneve; int /*<<< orphan*/  geneve_udp_port; int /*<<< orphan*/  set_geneve_udp_port_flg; int /*<<< orphan*/  tunnel_clss_l2geneve; int /*<<< orphan*/  vxlan_udp_port; int /*<<< orphan*/  set_vxlan_udp_port_flg; int /*<<< orphan*/  tunnel_clss_vxlan; } ;
struct TYPE_2__ {struct qed_tunnel_info tunnel; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qed_set_ramrod_tunnel_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_set_pf_update_tunn_mode (struct qed_tunnel_info*,struct qed_tunnel_info*,int) ; 
 int /*<<< orphan*/  qed_set_ramrod_tunnel_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_set_tunn_cls_info (struct qed_tunnel_info*,struct qed_tunnel_info*) ; 
 int /*<<< orphan*/  qed_set_tunn_ports (struct qed_tunnel_info*,struct qed_tunnel_info*) ; 

__attribute__((used)) static void
qed_tunn_set_pf_update_params(struct qed_hwfn *p_hwfn,
			      struct qed_tunnel_info *p_src,
			      struct pf_update_tunnel_config *p_tunn_cfg)
{
	struct qed_tunnel_info *p_tun = &p_hwfn->cdev->tunnel;

	qed_set_pf_update_tunn_mode(p_tun, p_src, false);
	qed_set_tunn_cls_info(p_tun, p_src);
	qed_set_tunn_ports(p_tun, p_src);

	qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_vxlan,
				    &p_tun->vxlan,
				    &p_tunn_cfg->set_vxlan_udp_port_flg,
				    &p_tunn_cfg->vxlan_udp_port,
				    &p_tun->vxlan_port);

	qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_l2geneve,
				    &p_tun->l2_geneve,
				    &p_tunn_cfg->set_geneve_udp_port_flg,
				    &p_tunn_cfg->geneve_udp_port,
				    &p_tun->geneve_port);

	__qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_ipgeneve,
				      &p_tun->ip_geneve);

	__qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_l2gre,
				      &p_tun->l2_gre);

	__qed_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_ipgre,
				      &p_tun->ip_gre);

	p_tunn_cfg->update_rx_pf_clss = p_tun->b_update_rx_cls;
}