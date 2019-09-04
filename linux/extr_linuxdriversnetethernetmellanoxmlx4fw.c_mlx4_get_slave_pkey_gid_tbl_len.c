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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/ * buf; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_PORT ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int /*<<< orphan*/  MLX4_GET (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  QUERY_PORT_CUR_MAX_GID_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_CUR_MAX_PKEY_OFFSET ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_get_slave_pkey_gid_tbl_len(struct mlx4_dev *dev, u8 port,
				    int *gid_tbl_len, int *pkey_tbl_len)
{
	struct mlx4_cmd_mailbox *mailbox;
	u32			*outbox;
	u16			field;
	int			err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	err =  mlx4_cmd_box(dev, 0, mailbox->dma, port, 0,
			    MLX4_CMD_QUERY_PORT, MLX4_CMD_TIME_CLASS_B,
			    MLX4_CMD_WRAPPED);
	if (err)
		goto out;

	outbox = mailbox->buf;

	MLX4_GET(field, outbox, QUERY_PORT_CUR_MAX_GID_OFFSET);
	*gid_tbl_len = field;

	MLX4_GET(field, outbox, QUERY_PORT_CUR_MAX_PKEY_OFFSET);
	*pkey_tbl_len = field;

out:
	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}