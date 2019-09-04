#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int tun_cls; } ;
struct TYPE_9__ {int tun_cls; } ;
struct TYPE_8__ {int tun_cls; } ;
struct TYPE_7__ {int tun_cls; } ;
struct TYPE_6__ {int tun_cls; } ;
struct qed_tunnel_info {TYPE_5__ ip_geneve; TYPE_4__ l2_geneve; TYPE_3__ ip_gre; TYPE_2__ l2_gre; TYPE_1__ vxlan; int /*<<< orphan*/  b_update_tx_cls; int /*<<< orphan*/  b_update_rx_cls; } ;

/* Variables and functions */
 int qed_tunn_clss_to_fw_clss (int) ; 

__attribute__((used)) static void qed_set_tunn_cls_info(struct qed_tunnel_info *p_tun,
				  struct qed_tunnel_info *p_src)
{
	int type;

	p_tun->b_update_rx_cls = p_src->b_update_rx_cls;
	p_tun->b_update_tx_cls = p_src->b_update_tx_cls;

	type = qed_tunn_clss_to_fw_clss(p_src->vxlan.tun_cls);
	p_tun->vxlan.tun_cls = type;
	type = qed_tunn_clss_to_fw_clss(p_src->l2_gre.tun_cls);
	p_tun->l2_gre.tun_cls = type;
	type = qed_tunn_clss_to_fw_clss(p_src->ip_gre.tun_cls);
	p_tun->ip_gre.tun_cls = type;
	type = qed_tunn_clss_to_fw_clss(p_src->l2_geneve.tun_cls);
	p_tun->l2_geneve.tun_cls = type;
	type = qed_tunn_clss_to_fw_clss(p_src->ip_geneve.tun_cls);
	p_tun->ip_geneve.tun_cls = type;
}