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
typedef  int /*<<< orphan*/  u32 ;
struct peak_canfd_priv {scalar_t__ cmd_buffer; } ;
struct pciefd_can {TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIEFD_REG_CAN_CMD_PORT_H ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_CMD_PORT_L ; 
 int /*<<< orphan*/  pciefd_can_writereg (struct pciefd_can*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pciefd_write_cmd(struct peak_canfd_priv *ucan)
{
	struct pciefd_can *priv = (struct pciefd_can *)ucan;
	unsigned long flags;

	/* 64-bits command is atomic */
	spin_lock_irqsave(&priv->board->cmd_lock, flags);

	pciefd_can_writereg(priv, *(u32 *)ucan->cmd_buffer,
			    PCIEFD_REG_CAN_CMD_PORT_L);
	pciefd_can_writereg(priv, *(u32 *)(ucan->cmd_buffer + 4),
			    PCIEFD_REG_CAN_CMD_PORT_H);

	spin_unlock_irqrestore(&priv->board->cmd_lock, flags);

	return 0;
}