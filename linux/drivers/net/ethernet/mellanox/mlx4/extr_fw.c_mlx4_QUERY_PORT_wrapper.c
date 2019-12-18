#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct mlx4_vhcr {int in_modifier; scalar_t__ op_modifier; } ;
struct TYPE_10__ {TYPE_3__* vf_oper; } ;
struct TYPE_11__ {TYPE_4__ master; } ;
struct mlx4_priv {TYPE_5__ mfunc; } ;
struct mlx4_port_cap {int link_state; } ;
struct TYPE_12__ {int function; int* port_type; int* pkey_table_len; } ;
struct mlx4_dev {TYPE_6__ caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;
struct mlx4_cmd_info {int dummy; } ;
struct TYPE_9__ {TYPE_2__* vport; } ;
struct TYPE_7__ {int mac; int link_state; } ;
struct TYPE_8__ {TYPE_1__ state; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFLA_VF_LINK_STATE_AUTO ; 
 int IFLA_VF_LINK_STATE_DISABLE ; 
 int IFLA_VF_LINK_STATE_ENABLE ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_PORT ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  MLX4_GET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX4_PORT_LINK_UP_MASK ; 
 int MLX4_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  MLX4_PUT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int MLX4_VF_PORT_NO_LINK_SENSE_MASK ; 
 int /*<<< orphan*/  QUERY_PORT_CUR_MAX_GID_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_CUR_MAX_PKEY_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_MAC_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_SUPPORTED_TYPE_OFFSET ; 
 int mlx4_QUERY_PORT (struct mlx4_dev*,int,struct mlx4_port_cap*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_get_slave_num_gids (struct mlx4_dev*,int,int) ; 
 scalar_t__ mlx4_is_bonded (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_slave_convert_port (struct mlx4_dev*,int,int) ; 

int mlx4_QUERY_PORT_wrapper(struct mlx4_dev *dev, int slave,
			    struct mlx4_vhcr *vhcr,
			    struct mlx4_cmd_mailbox *inbox,
			    struct mlx4_cmd_mailbox *outbox,
			    struct mlx4_cmd_info *cmd)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	u64 def_mac;
	u8 port_type;
	u16 short_field;
	int err;
	int admin_link_state;
	int port = mlx4_slave_convert_port(dev, slave,
					   vhcr->in_modifier & 0xFF);

#define MLX4_VF_PORT_NO_LINK_SENSE_MASK	0xE0
#define MLX4_PORT_LINK_UP_MASK		0x80
#define QUERY_PORT_CUR_MAX_PKEY_OFFSET	0x0c
#define QUERY_PORT_CUR_MAX_GID_OFFSET	0x0e

	if (port < 0)
		return -EINVAL;

	/* Protect against untrusted guests: enforce that this is the
	 * QUERY_PORT general query.
	 */
	if (vhcr->op_modifier || vhcr->in_modifier & ~0xFF)
		return -EINVAL;

	vhcr->in_modifier = port;

	err = mlx4_cmd_box(dev, 0, outbox->dma, vhcr->in_modifier, 0,
			   MLX4_CMD_QUERY_PORT, MLX4_CMD_TIME_CLASS_B,
			   MLX4_CMD_NATIVE);

	if (!err && dev->caps.function != slave) {
		def_mac = priv->mfunc.master.vf_oper[slave].vport[vhcr->in_modifier].state.mac;
		MLX4_PUT(outbox->buf, def_mac, QUERY_PORT_MAC_OFFSET);

		/* get port type - currently only eth is enabled */
		MLX4_GET(port_type, outbox->buf,
			 QUERY_PORT_SUPPORTED_TYPE_OFFSET);

		/* No link sensing allowed */
		port_type &= MLX4_VF_PORT_NO_LINK_SENSE_MASK;
		/* set port type to currently operating port type */
		port_type |= (dev->caps.port_type[vhcr->in_modifier] & 0x3);

		admin_link_state = priv->mfunc.master.vf_oper[slave].vport[vhcr->in_modifier].state.link_state;
		if (IFLA_VF_LINK_STATE_ENABLE == admin_link_state)
			port_type |= MLX4_PORT_LINK_UP_MASK;
		else if (IFLA_VF_LINK_STATE_DISABLE == admin_link_state)
			port_type &= ~MLX4_PORT_LINK_UP_MASK;
		else if (IFLA_VF_LINK_STATE_AUTO == admin_link_state && mlx4_is_bonded(dev)) {
			int other_port = (port == 1) ? 2 : 1;
			struct mlx4_port_cap port_cap;

			err = mlx4_QUERY_PORT(dev, other_port, &port_cap);
			if (err)
				goto out;
			port_type |= (port_cap.link_state << 7);
		}

		MLX4_PUT(outbox->buf, port_type,
			 QUERY_PORT_SUPPORTED_TYPE_OFFSET);

		if (dev->caps.port_type[vhcr->in_modifier] == MLX4_PORT_TYPE_ETH)
			short_field = mlx4_get_slave_num_gids(dev, slave, port);
		else
			short_field = 1; /* slave max gids */
		MLX4_PUT(outbox->buf, short_field,
			 QUERY_PORT_CUR_MAX_GID_OFFSET);

		short_field = dev->caps.pkey_table_len[vhcr->in_modifier];
		MLX4_PUT(outbox->buf, short_field,
			 QUERY_PORT_CUR_MAX_PKEY_OFFSET);
	}
out:
	return err;
}