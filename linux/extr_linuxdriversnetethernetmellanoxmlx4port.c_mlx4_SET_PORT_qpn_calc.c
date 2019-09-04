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
typedef  int u8 ;
typedef  int u32 ;
struct mlx4_set_port_rqp_calc_context {int /*<<< orphan*/  vlan_miss; scalar_t__ intra_vlan_miss; int /*<<< orphan*/  no_vlan; scalar_t__ intra_no_vlan; void* mcast; void* promisc; int /*<<< orphan*/  n_mac; void* base_qpn; } ;
struct TYPE_2__ {int flags; scalar_t__ steering_mode; int /*<<< orphan*/  log_num_macs; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; struct mlx4_set_port_rqp_calc_context* buf; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int MCAST_DEFAULT ; 
 int MCAST_DIRECT ; 
 int /*<<< orphan*/  MLX4_CMD_SET_PORT ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int MLX4_DEV_CAP_FLAG_VEP_MC_STEER ; 
 int /*<<< orphan*/  MLX4_NO_VLAN_IDX ; 
 int /*<<< orphan*/  MLX4_SET_PORT_ETH_OPCODE ; 
 int MLX4_SET_PORT_RQP_CALC ; 
 scalar_t__ MLX4_STEERING_MODE_A0 ; 
 int /*<<< orphan*/  MLX4_VLAN_MISS_IDX ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int SET_PORT_MC_PROMISC_SHIFT ; 
 int SET_PORT_PROMISC_SHIFT ; 
 void* cpu_to_be32 (int) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_SET_PORT_qpn_calc(struct mlx4_dev *dev, u8 port, u32 base_qpn,
			   u8 promisc)
{
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_set_port_rqp_calc_context *context;
	int err;
	u32 in_mod;
	u32 m_promisc = (dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_MC_STEER) ?
		MCAST_DIRECT : MCAST_DEFAULT;

	if (dev->caps.steering_mode != MLX4_STEERING_MODE_A0)
		return 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	context = mailbox->buf;
	context->base_qpn = cpu_to_be32(base_qpn);
	context->n_mac = dev->caps.log_num_macs;
	context->promisc = cpu_to_be32(promisc << SET_PORT_PROMISC_SHIFT |
				       base_qpn);
	context->mcast = cpu_to_be32(m_promisc << SET_PORT_MC_PROMISC_SHIFT |
				     base_qpn);
	context->intra_no_vlan = 0;
	context->no_vlan = MLX4_NO_VLAN_IDX;
	context->intra_vlan_miss = 0;
	context->vlan_miss = MLX4_VLAN_MISS_IDX;

	in_mod = MLX4_SET_PORT_RQP_CALC << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, MLX4_SET_PORT_ETH_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_WRAPPED);

	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}