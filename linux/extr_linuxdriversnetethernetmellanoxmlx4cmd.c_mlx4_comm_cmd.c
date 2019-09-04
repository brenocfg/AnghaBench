#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx4_dev {TYPE_1__* persist; } ;
struct TYPE_5__ {scalar_t__ use_events; } ;
struct TYPE_6__ {TYPE_2__ cmd; } ;
struct TYPE_4__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STAT_INTERNAL_ERR ; 
 int MLX4_DEVICE_STATE_INTERNAL_ERROR ; 
 int mlx4_comm_cmd_poll (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int mlx4_comm_cmd_wait (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_3__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_status_to_errno (int /*<<< orphan*/ ) ; 

int mlx4_comm_cmd(struct mlx4_dev *dev, u8 cmd, u16 param,
		  u16 op, unsigned long timeout)
{
	if (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)
		return mlx4_status_to_errno(CMD_STAT_INTERNAL_ERR);

	if (mlx4_priv(dev)->cmd.use_events)
		return mlx4_comm_cmd_wait(dev, cmd, param, op, timeout);
	return mlx4_comm_cmd_poll(dev, cmd, param, timeout);
}