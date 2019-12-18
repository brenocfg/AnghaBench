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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct mlx4_func {int bus; int device; int function; int physical_function; int rsvd_eqs; int max_eq; int rsvd_uars; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_FUNC ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_GET (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  QUERY_FUNC_BUS_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_DEVICE_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_FUNCTION_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_MAX_EQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_PHYSICAL_FUNCTION_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_RSVD_EQS_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_RSVD_UARS_OFFSET ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_QUERY_FUNC(struct mlx4_dev *dev, struct mlx4_func *func, int slave)
{
	struct mlx4_cmd_mailbox *mailbox;
	u32 *outbox;
	u8 in_modifier;
	u8 field;
	u16 field16;
	int err;

#define QUERY_FUNC_BUS_OFFSET			0x00
#define QUERY_FUNC_DEVICE_OFFSET		0x01
#define QUERY_FUNC_FUNCTION_OFFSET		0x01
#define QUERY_FUNC_PHYSICAL_FUNCTION_OFFSET	0x03
#define QUERY_FUNC_RSVD_EQS_OFFSET		0x04
#define QUERY_FUNC_MAX_EQ_OFFSET		0x06
#define QUERY_FUNC_RSVD_UARS_OFFSET		0x0b

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	outbox = mailbox->buf;

	in_modifier = slave;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, in_modifier, 0,
			   MLX4_CMD_QUERY_FUNC,
			   MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	if (err)
		goto out;

	MLX4_GET(field, outbox, QUERY_FUNC_BUS_OFFSET);
	func->bus = field & 0xf;
	MLX4_GET(field, outbox, QUERY_FUNC_DEVICE_OFFSET);
	func->device = field & 0xf1;
	MLX4_GET(field, outbox, QUERY_FUNC_FUNCTION_OFFSET);
	func->function = field & 0x7;
	MLX4_GET(field, outbox, QUERY_FUNC_PHYSICAL_FUNCTION_OFFSET);
	func->physical_function = field & 0xf;
	MLX4_GET(field16, outbox, QUERY_FUNC_RSVD_EQS_OFFSET);
	func->rsvd_eqs = field16 & 0xffff;
	MLX4_GET(field16, outbox, QUERY_FUNC_MAX_EQ_OFFSET);
	func->max_eq = field16 & 0xffff;
	MLX4_GET(field, outbox, QUERY_FUNC_RSVD_UARS_OFFSET);
	func->rsvd_uars = field & 0x0f;

	mlx4_dbg(dev, "Bus: %d, Device: %d, Function: %d, Physical function: %d, Max EQs: %d, Reserved EQs: %d, Reserved UARs: %d\n",
		 func->bus, func->device, func->function, func->physical_function,
		 func->max_eq, func->rsvd_eqs, func->rsvd_uars);

out:
	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}