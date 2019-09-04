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
typedef  scalar_t__ u8 ;
struct mlx4_vhcr {int dummy; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; scalar_t__* buf; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_FW ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 scalar_t__ MLX4_INVALID_SLAVE_ID ; 
 scalar_t__ QUERY_FW_OUT_SIZE ; 
 size_t QUERY_FW_PPF_ID ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_QUERY_FW_wrapper(struct mlx4_dev *dev, int slave,
			  struct mlx4_vhcr *vhcr,
			  struct mlx4_cmd_mailbox *inbox,
			  struct mlx4_cmd_mailbox *outbox,
			  struct mlx4_cmd_info *cmd)
{
	u8 *outbuf;
	int err;

	outbuf = outbox->buf;
	err = mlx4_cmd_box(dev, 0, outbox->dma, 0, 0, MLX4_CMD_QUERY_FW,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	if (err)
		return err;

	/* for slaves, set pci PPF ID to invalid and zero out everything
	 * else except FW version */
	outbuf[0] = outbuf[1] = 0;
	memset(&outbuf[8], 0, QUERY_FW_OUT_SIZE - 8);
	outbuf[QUERY_FW_PPF_ID] = MLX4_INVALID_SLAVE_ID;

	return 0;
}