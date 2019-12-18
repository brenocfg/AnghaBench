#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_MAD_DEMUX_GETRESP_ATTR_OFFSET ; 
 int /*<<< orphan*/  MLX4_CMD_MAD_DEMUX_SET_ATTR_OFFSET ; 
 int /*<<< orphan*/  MLX4_CMD_MAD_DEMUX_TRAP_ATTR_OFFSET ; 
 int /*<<< orphan*/  MLX4_CMD_MAD_DEMUX_TRAP_REPRESS_ATTR_OFFSET ; 
 int /*<<< orphan*/  MLX4_GET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,scalar_t__) ; 

__attribute__((used)) static int mlx4_check_smp_firewall_active(struct mlx4_dev *dev,
					  struct mlx4_cmd_mailbox *mailbox)
{
#define MLX4_CMD_MAD_DEMUX_SET_ATTR_OFFSET		0x10
#define MLX4_CMD_MAD_DEMUX_GETRESP_ATTR_OFFSET		0x20
#define MLX4_CMD_MAD_DEMUX_TRAP_ATTR_OFFSET		0x40
#define MLX4_CMD_MAD_DEMUX_TRAP_REPRESS_ATTR_OFFSET	0x70

	u32 set_attr_mask, getresp_attr_mask;
	u32 trap_attr_mask, traprepress_attr_mask;

	MLX4_GET(set_attr_mask, mailbox->buf,
		 MLX4_CMD_MAD_DEMUX_SET_ATTR_OFFSET);
	mlx4_dbg(dev, "SMP firewall set_attribute_mask = 0x%x\n",
		 set_attr_mask);

	MLX4_GET(getresp_attr_mask, mailbox->buf,
		 MLX4_CMD_MAD_DEMUX_GETRESP_ATTR_OFFSET);
	mlx4_dbg(dev, "SMP firewall getresp_attribute_mask = 0x%x\n",
		 getresp_attr_mask);

	MLX4_GET(trap_attr_mask, mailbox->buf,
		 MLX4_CMD_MAD_DEMUX_TRAP_ATTR_OFFSET);
	mlx4_dbg(dev, "SMP firewall trap_attribute_mask = 0x%x\n",
		 trap_attr_mask);

	MLX4_GET(traprepress_attr_mask, mailbox->buf,
		 MLX4_CMD_MAD_DEMUX_TRAP_REPRESS_ATTR_OFFSET);
	mlx4_dbg(dev, "SMP firewall traprepress_attribute_mask = 0x%x\n",
		 traprepress_attr_mask);

	if (set_attr_mask && getresp_attr_mask && trap_attr_mask &&
	    traprepress_attr_mask)
		return 1;

	return 0;
}