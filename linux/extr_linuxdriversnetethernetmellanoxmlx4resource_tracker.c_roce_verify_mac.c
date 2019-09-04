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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int grh_mylmc; } ;
struct mlx4_qp_context {TYPE_1__ pri_path; int /*<<< orphan*/  flags; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {scalar_t__ buf; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ MLX4_QP_ST_MLX ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mac_find_smac_ix_in_slave (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ mlx4_is_eth (struct mlx4_dev*,int) ; 

__attribute__((used)) static int roce_verify_mac(struct mlx4_dev *dev, int slave,
				struct mlx4_qp_context *qpc,
				struct mlx4_cmd_mailbox *inbox)
{
	u64 mac;
	int port;
	u32 ts = (be32_to_cpu(qpc->flags) >> 16) & 0xff;
	u8 sched = *(u8 *)(inbox->buf + 64);
	u8 smac_ix;

	port = (sched >> 6 & 1) + 1;
	if (mlx4_is_eth(dev, port) && (ts != MLX4_QP_ST_MLX)) {
		smac_ix = qpc->pri_path.grh_mylmc & 0x7f;
		if (mac_find_smac_ix_in_slave(dev, slave, port, smac_ix, &mac))
			return -ENOENT;
	}
	return 0;
}