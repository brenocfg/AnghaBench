#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  qpn; } ;
struct mlx5dr_qp {TYPE_2__ mqp; } ;
struct TYPE_7__ {int /*<<< orphan*/  roce_min_src_udp; } ;
struct TYPE_8__ {TYPE_3__ caps; } ;
struct mlx5dr_domain {int /*<<< orphan*/  mdev; TYPE_4__ info; TYPE_1__* send_ring; } ;
struct dr_qp_rts_attr {int timeout; int retry_cnt; int rnr_retry; } ;
struct dr_qp_rtr_attr {int mtu; int min_rnr_timer; int port_num; int /*<<< orphan*/  udp_src_port; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  dgid_attr; } ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;
struct TYPE_5__ {struct mlx5dr_qp* qp; } ;

/* Variables and functions */
 int IB_MTU_1024 ; 
 int dr_cmd_modify_qp_init2rtr (int /*<<< orphan*/ ,struct mlx5dr_qp*,struct dr_qp_rtr_attr*) ; 
 int dr_cmd_modify_qp_rtr2rts (int /*<<< orphan*/ ,struct mlx5dr_qp*,struct dr_qp_rts_attr*) ; 
 int dr_modify_qp_rst2init (int /*<<< orphan*/ ,struct mlx5dr_qp*,int) ; 
 int mlx5dr_cmd_query_gid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dr_prepare_qp_to_rts(struct mlx5dr_domain *dmn)
{
	struct mlx5dr_qp *dr_qp = dmn->send_ring->qp;
	struct dr_qp_rts_attr rts_attr = {};
	struct dr_qp_rtr_attr rtr_attr = {};
	enum ib_mtu mtu = IB_MTU_1024;
	u16 gid_index = 0;
	int port = 1;
	int ret;

	/* Init */
	ret = dr_modify_qp_rst2init(dmn->mdev, dr_qp, port);
	if (ret)
		return ret;

	/* RTR */
	ret = mlx5dr_cmd_query_gid(dmn->mdev, port, gid_index, &rtr_attr.dgid_attr);
	if (ret)
		return ret;

	rtr_attr.mtu		= mtu;
	rtr_attr.qp_num		= dr_qp->mqp.qpn;
	rtr_attr.min_rnr_timer	= 12;
	rtr_attr.port_num	= port;
	rtr_attr.sgid_index	= gid_index;
	rtr_attr.udp_src_port	= dmn->info.caps.roce_min_src_udp;

	ret = dr_cmd_modify_qp_init2rtr(dmn->mdev, dr_qp, &rtr_attr);
	if (ret)
		return ret;

	/* RTS */
	rts_attr.timeout	= 14;
	rts_attr.retry_cnt	= 7;
	rts_attr.rnr_retry	= 7;

	ret = dr_cmd_modify_qp_rtr2rts(dmn->mdev, dr_qp, &rts_attr);
	if (ret)
		return ret;

	return 0;
}