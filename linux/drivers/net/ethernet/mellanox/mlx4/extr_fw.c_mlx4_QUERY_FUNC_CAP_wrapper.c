#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_16__ {scalar_t__ vlan_proto; } ;
struct mlx4_vport_oper_state {TYPE_8__ state; } ;
struct mlx4_vhcr {int op_modifier; int in_modifier; } ;
struct mlx4_slave_state {int vst_qinq_supported; } ;
struct TYPE_10__ {TYPE_1__* res_alloc; } ;
struct TYPE_13__ {TYPE_2__ res_tracker; struct mlx4_slave_state* slave_state; TYPE_4__* vf_oper; } ;
struct TYPE_14__ {TYPE_5__ master; } ;
struct mlx4_priv {TYPE_6__ mfunc; } ;
struct mlx4_func {int max_eq; int rsvd_eqs; } ;
struct TYPE_15__ {int* phys_port_id; int function_caps; int num_qps; int num_srqs; int num_cqs; int flags2; int num_eqs; int reserved_eqs; int num_mpts; int num_mtts; int num_mgms; int num_amgms; int reserved_lkey; int /*<<< orphan*/  num_ports; scalar_t__* phv_bit; } ;
struct TYPE_11__ {int base_proxy_sqpn; int base_tunnel_sqpn; } ;
struct mlx4_dev {TYPE_7__ caps; TYPE_3__ phys_caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  buf; } ;
struct mlx4_cmd_info {int dummy; } ;
struct mlx4_active_ports {int /*<<< orphan*/  ports; } ;
struct TYPE_12__ {struct mlx4_vport_oper_state* vport; } ;
struct TYPE_9__ {int* quota; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int MLX4_DEV_CAP_FLAG2_SYS_EQS ; 
 int /*<<< orphan*/  MLX4_PUT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_CQ_QUOTA_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_CQ_QUOTA_OFFSET_DEP ; 
 int QUERY_FUNC_CAP_EXTRA_FLAGS_A0_QP_ALLOC_FLAG ; 
 int QUERY_FUNC_CAP_EXTRA_FLAGS_BF_QP_ALLOC_FLAG ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_EXTRA_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_FLAGS0_OFFSET ; 
 size_t QUERY_FUNC_CAP_FLAGS1_NIC_INFO ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_FLAGS1_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_FLAGS_OFFSET ; 
 size_t QUERY_FUNC_CAP_FLAG_ETH ; 
 size_t QUERY_FUNC_CAP_FLAG_QUOTAS ; 
 size_t QUERY_FUNC_CAP_FLAG_RDMA ; 
 size_t QUERY_FUNC_CAP_FLAG_RESD_LKEY ; 
 size_t QUERY_FUNC_CAP_FLAG_VALID_MAILBOX ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_FMR_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MAX_EQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MCG_QUOTA_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MCG_QUOTA_OFFSET_DEP ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MPT_QUOTA_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MPT_QUOTA_OFFSET_DEP ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MTT_QUOTA_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MTT_QUOTA_OFFSET_DEP ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_NUM_PORTS_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_PF_BHVR_OFFSET ; 
 size_t QUERY_FUNC_CAP_PHV_BIT ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_PHYS_PORT_ID ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_PHYS_PORT_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_PRIV_VF_QKEY_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP0_PROXY ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP0_TUNNEL ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP1_PROXY ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP1_TUNNEL ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP_QUOTA_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP_QUOTA_OFFSET_DEP ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP_RESD_LKEY_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_RESERVED_EQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET_DEP ; 
 int QUERY_FUNC_CAP_SUPPORTS_NON_POWER_OF_2_NUM_EQS ; 
 int QUERY_FUNC_CAP_SUPPORTS_VST_QINQ ; 
 size_t QUERY_FUNC_CAP_VF_ENABLE_QP0 ; 
 size_t QUERY_FUNC_CAP_VLAN_OFFLOAD_DISABLE ; 
 size_t RES_CQ ; 
 size_t RES_MPT ; 
 size_t RES_MTT ; 
 size_t RES_QP ; 
 size_t RES_SRQ ; 
 int /*<<< orphan*/  bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t find_first_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 size_t min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_QUERY_FUNC (struct mlx4_dev*,struct mlx4_func*,int) ; 
 struct mlx4_active_ports mlx4_get_active_ports (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_get_parav_qkey (struct mlx4_dev*,int,int*) ; 
 int mlx4_handle_vst_qinq (struct mlx4_priv*,int,size_t) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_slave_convert_port (struct mlx4_dev*,int,int) ; 
 scalar_t__ mlx4_vf_smi_enabled (struct mlx4_dev*,int,size_t) ; 
 int rounddown_pow_of_two (int) ; 

int mlx4_QUERY_FUNC_CAP_wrapper(struct mlx4_dev *dev, int slave,
				struct mlx4_vhcr *vhcr,
				struct mlx4_cmd_mailbox *inbox,
				struct mlx4_cmd_mailbox *outbox,
				struct mlx4_cmd_info *cmd)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	u8	field, port;
	u32	size, proxy_qp, qkey;
	int	err = 0;
	struct mlx4_func func;

#define QUERY_FUNC_CAP_FLAGS_OFFSET		0x0
#define QUERY_FUNC_CAP_NUM_PORTS_OFFSET		0x1
#define QUERY_FUNC_CAP_PF_BHVR_OFFSET		0x4
#define QUERY_FUNC_CAP_FMR_OFFSET		0x8
#define QUERY_FUNC_CAP_QP_QUOTA_OFFSET_DEP	0x10
#define QUERY_FUNC_CAP_CQ_QUOTA_OFFSET_DEP	0x14
#define QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET_DEP	0x18
#define QUERY_FUNC_CAP_MPT_QUOTA_OFFSET_DEP	0x20
#define QUERY_FUNC_CAP_MTT_QUOTA_OFFSET_DEP	0x24
#define QUERY_FUNC_CAP_MCG_QUOTA_OFFSET_DEP	0x28
#define QUERY_FUNC_CAP_MAX_EQ_OFFSET		0x2c
#define QUERY_FUNC_CAP_RESERVED_EQ_OFFSET	0x30
#define QUERY_FUNC_CAP_QP_RESD_LKEY_OFFSET	0x48

#define QUERY_FUNC_CAP_QP_QUOTA_OFFSET		0x50
#define QUERY_FUNC_CAP_CQ_QUOTA_OFFSET		0x54
#define QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET		0x58
#define QUERY_FUNC_CAP_MPT_QUOTA_OFFSET		0x60
#define QUERY_FUNC_CAP_MTT_QUOTA_OFFSET		0x64
#define QUERY_FUNC_CAP_MCG_QUOTA_OFFSET		0x68

#define QUERY_FUNC_CAP_EXTRA_FLAGS_OFFSET	0x6c

#define QUERY_FUNC_CAP_FMR_FLAG			0x80
#define QUERY_FUNC_CAP_FLAG_RDMA		0x40
#define QUERY_FUNC_CAP_FLAG_ETH			0x80
#define QUERY_FUNC_CAP_FLAG_QUOTAS		0x10
#define QUERY_FUNC_CAP_FLAG_RESD_LKEY		0x08
#define QUERY_FUNC_CAP_FLAG_VALID_MAILBOX	0x04

#define QUERY_FUNC_CAP_EXTRA_FLAGS_BF_QP_ALLOC_FLAG	(1UL << 31)
#define QUERY_FUNC_CAP_EXTRA_FLAGS_A0_QP_ALLOC_FLAG	(1UL << 30)

/* when opcode modifier = 1 */
#define QUERY_FUNC_CAP_PHYS_PORT_OFFSET		0x3
#define QUERY_FUNC_CAP_PRIV_VF_QKEY_OFFSET	0x4
#define QUERY_FUNC_CAP_FLAGS0_OFFSET		0x8
#define QUERY_FUNC_CAP_FLAGS1_OFFSET		0xc

#define QUERY_FUNC_CAP_QP0_TUNNEL		0x10
#define QUERY_FUNC_CAP_QP0_PROXY		0x14
#define QUERY_FUNC_CAP_QP1_TUNNEL		0x18
#define QUERY_FUNC_CAP_QP1_PROXY		0x1c
#define QUERY_FUNC_CAP_PHYS_PORT_ID		0x28

#define QUERY_FUNC_CAP_FLAGS1_FORCE_MAC		0x40
#define QUERY_FUNC_CAP_FLAGS1_FORCE_VLAN	0x80
#define QUERY_FUNC_CAP_FLAGS1_NIC_INFO			0x10
#define QUERY_FUNC_CAP_VF_ENABLE_QP0		0x08

#define QUERY_FUNC_CAP_FLAGS0_FORCE_PHY_WQE_GID 0x80
#define QUERY_FUNC_CAP_PHV_BIT			0x40
#define QUERY_FUNC_CAP_VLAN_OFFLOAD_DISABLE	0x20

#define QUERY_FUNC_CAP_SUPPORTS_VST_QINQ	BIT(30)
#define QUERY_FUNC_CAP_SUPPORTS_NON_POWER_OF_2_NUM_EQS BIT(31)

	if (vhcr->op_modifier == 1) {
		struct mlx4_active_ports actv_ports =
			mlx4_get_active_ports(dev, slave);
		int converted_port = mlx4_slave_convert_port(
				dev, slave, vhcr->in_modifier);
		struct mlx4_vport_oper_state *vp_oper;

		if (converted_port < 0)
			return -EINVAL;

		vhcr->in_modifier = converted_port;
		/* phys-port = logical-port */
		field = vhcr->in_modifier -
			find_first_bit(actv_ports.ports, dev->caps.num_ports);
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_PHYS_PORT_OFFSET);

		port = vhcr->in_modifier;
		proxy_qp = dev->phys_caps.base_proxy_sqpn + 8 * slave + port - 1;

		/* Set nic_info bit to mark new fields support */
		field  = QUERY_FUNC_CAP_FLAGS1_NIC_INFO;

		if (mlx4_vf_smi_enabled(dev, slave, port) &&
		    !mlx4_get_parav_qkey(dev, proxy_qp, &qkey)) {
			field |= QUERY_FUNC_CAP_VF_ENABLE_QP0;
			MLX4_PUT(outbox->buf, qkey,
				 QUERY_FUNC_CAP_PRIV_VF_QKEY_OFFSET);
		}
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_FLAGS1_OFFSET);

		/* size is now the QP number */
		size = dev->phys_caps.base_tunnel_sqpn + 8 * slave + port - 1;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP0_TUNNEL);

		size += 2;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP1_TUNNEL);

		MLX4_PUT(outbox->buf, proxy_qp, QUERY_FUNC_CAP_QP0_PROXY);
		proxy_qp += 2;
		MLX4_PUT(outbox->buf, proxy_qp, QUERY_FUNC_CAP_QP1_PROXY);

		MLX4_PUT(outbox->buf, dev->caps.phys_port_id[vhcr->in_modifier],
			 QUERY_FUNC_CAP_PHYS_PORT_ID);

		vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
		err = mlx4_handle_vst_qinq(priv, slave, port);
		if (err)
			return err;

		field = 0;
		if (dev->caps.phv_bit[port])
			field |= QUERY_FUNC_CAP_PHV_BIT;
		if (vp_oper->state.vlan_proto == htons(ETH_P_8021AD))
			field |= QUERY_FUNC_CAP_VLAN_OFFLOAD_DISABLE;
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_FLAGS0_OFFSET);

	} else if (vhcr->op_modifier == 0) {
		struct mlx4_active_ports actv_ports =
			mlx4_get_active_ports(dev, slave);
		struct mlx4_slave_state *slave_state =
			&priv->mfunc.master.slave_state[slave];

		/* enable rdma and ethernet interfaces, new quota locations,
		 * and reserved lkey
		 */
		field = (QUERY_FUNC_CAP_FLAG_ETH | QUERY_FUNC_CAP_FLAG_RDMA |
			 QUERY_FUNC_CAP_FLAG_QUOTAS | QUERY_FUNC_CAP_FLAG_VALID_MAILBOX |
			 QUERY_FUNC_CAP_FLAG_RESD_LKEY);
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_FLAGS_OFFSET);

		field = min(
			bitmap_weight(actv_ports.ports, dev->caps.num_ports),
			dev->caps.num_ports);
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_NUM_PORTS_OFFSET);

		size = dev->caps.function_caps; /* set PF behaviours */
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_PF_BHVR_OFFSET);

		field = 0; /* protected FMR support not available as yet */
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_FMR_OFFSET);

		size = priv->mfunc.master.res_tracker.res_alloc[RES_QP].quota[slave];
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP_QUOTA_OFFSET);
		size = dev->caps.num_qps;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP_QUOTA_OFFSET_DEP);

		size = priv->mfunc.master.res_tracker.res_alloc[RES_SRQ].quota[slave];
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET);
		size = dev->caps.num_srqs;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET_DEP);

		size = priv->mfunc.master.res_tracker.res_alloc[RES_CQ].quota[slave];
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_CQ_QUOTA_OFFSET);
		size = dev->caps.num_cqs;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_CQ_QUOTA_OFFSET_DEP);

		if (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS) ||
		    mlx4_QUERY_FUNC(dev, &func, slave)) {
			size = vhcr->in_modifier &
				QUERY_FUNC_CAP_SUPPORTS_NON_POWER_OF_2_NUM_EQS ?
				dev->caps.num_eqs :
				rounddown_pow_of_two(dev->caps.num_eqs);
			MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MAX_EQ_OFFSET);
			size = dev->caps.reserved_eqs;
			MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_RESERVED_EQ_OFFSET);
		} else {
			size = vhcr->in_modifier &
				QUERY_FUNC_CAP_SUPPORTS_NON_POWER_OF_2_NUM_EQS ?
				func.max_eq :
				rounddown_pow_of_two(func.max_eq);
			MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MAX_EQ_OFFSET);
			size = func.rsvd_eqs;
			MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_RESERVED_EQ_OFFSET);
		}

		size = priv->mfunc.master.res_tracker.res_alloc[RES_MPT].quota[slave];
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MPT_QUOTA_OFFSET);
		size = dev->caps.num_mpts;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MPT_QUOTA_OFFSET_DEP);

		size = priv->mfunc.master.res_tracker.res_alloc[RES_MTT].quota[slave];
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MTT_QUOTA_OFFSET);
		size = dev->caps.num_mtts;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MTT_QUOTA_OFFSET_DEP);

		size = dev->caps.num_mgms + dev->caps.num_amgms;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MCG_QUOTA_OFFSET);
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MCG_QUOTA_OFFSET_DEP);

		size = QUERY_FUNC_CAP_EXTRA_FLAGS_BF_QP_ALLOC_FLAG |
			QUERY_FUNC_CAP_EXTRA_FLAGS_A0_QP_ALLOC_FLAG;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_EXTRA_FLAGS_OFFSET);

		size = dev->caps.reserved_lkey + ((slave << 8) & 0xFF00);
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP_RESD_LKEY_OFFSET);

		if (vhcr->in_modifier & QUERY_FUNC_CAP_SUPPORTS_VST_QINQ)
			slave_state->vst_qinq_supported = true;

	} else
		err = -EINVAL;

	return err;
}