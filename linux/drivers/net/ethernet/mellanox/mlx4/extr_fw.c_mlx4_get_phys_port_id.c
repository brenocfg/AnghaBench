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
typedef  size_t u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_2__ {size_t num_ports; int* phys_port_id; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {size_t* buf; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_MOD_STAT_CFG ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_GET (size_t,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_STAT_CFG_GUID_H ; 
 int /*<<< orphan*/  MOD_STAT_CFG_GUID_L ; 
 size_t MOD_STAT_CFG_PORT_OFFSET ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,size_t) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_get_phys_port_id(struct mlx4_dev *dev)
{
	u8 port;
	u32 *outbox;
	struct mlx4_cmd_mailbox *mailbox;
	u32 in_mod;
	u32 guid_hi, guid_lo;
	int err, ret = 0;
#define MOD_STAT_CFG_PORT_OFFSET 8
#define MOD_STAT_CFG_GUID_H	 0X14
#define MOD_STAT_CFG_GUID_L	 0X1c

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	outbox = mailbox->buf;

	for (port = 1; port <= dev->caps.num_ports; port++) {
		in_mod = port << MOD_STAT_CFG_PORT_OFFSET;
		err = mlx4_cmd_box(dev, 0, mailbox->dma, in_mod, 0x2,
				   MLX4_CMD_MOD_STAT_CFG, MLX4_CMD_TIME_CLASS_A,
				   MLX4_CMD_NATIVE);
		if (err) {
			mlx4_err(dev, "Fail to get port %d uplink guid\n",
				 port);
			ret = err;
		} else {
			MLX4_GET(guid_hi, outbox, MOD_STAT_CFG_GUID_H);
			MLX4_GET(guid_lo, outbox, MOD_STAT_CFG_GUID_L);
			dev->caps.phys_port_id[port] = (u64)guid_lo |
						       (u64)guid_hi << 32;
		}
	}
	mlx4_free_cmd_mailbox(dev, mailbox);
	return ret;
}