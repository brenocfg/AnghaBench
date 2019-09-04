#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_ports; scalar_t__* port_type; } ;
struct mlx4_dev {TYPE_2__ caps; TYPE_1__* persist; } ;
struct mlx4_cmd_mailbox {int dummy; } ;
struct mlx4_active_ports {int /*<<< orphan*/  ports; } ;
struct TYPE_3__ {int num_vfs; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 scalar_t__ MLX4_PORT_TYPE_ETH ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 
 struct mlx4_active_ports mlx4_get_active_ports (struct mlx4_dev*,int) ; 
 int mlx4_reset_roce_port_gids (struct mlx4_dev*,int,int,struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int,int,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

void mlx4_reset_roce_gids(struct mlx4_dev *dev, int slave)
{
	struct mlx4_active_ports actv_ports;
	struct mlx4_cmd_mailbox *mailbox;
	int num_eth_ports, err;
	int i;

	if (slave < 0 || slave > dev->persist->num_vfs)
		return;

	actv_ports = mlx4_get_active_ports(dev, slave);

	for (i = 0, num_eth_ports = 0; i < dev->caps.num_ports; i++) {
		if (test_bit(i, actv_ports.ports)) {
			if (dev->caps.port_type[i + 1] != MLX4_PORT_TYPE_ETH)
				continue;
			num_eth_ports++;
		}
	}

	if (!num_eth_ports)
		return;

	/* have ETH ports.  Alloc mailbox for SET_PORT command */
	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return;

	for (i = 0; i < dev->caps.num_ports; i++) {
		if (test_bit(i, actv_ports.ports)) {
			if (dev->caps.port_type[i + 1] != MLX4_PORT_TYPE_ETH)
				continue;
			err = mlx4_reset_roce_port_gids(dev, slave, i + 1, mailbox);
			if (err)
				mlx4_warn(dev, "Could not reset ETH port GID table for slave %d, port %d (%d)\n",
					  slave, i + 1, err);
		}
	}

	mlx4_free_cmd_mailbox(dev, mailbox);
	return;
}