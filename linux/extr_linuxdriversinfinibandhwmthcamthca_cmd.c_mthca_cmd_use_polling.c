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
struct TYPE_2__ {int max_cmds; int /*<<< orphan*/  poll_sem; int /*<<< orphan*/  context; int /*<<< orphan*/  event_sem; int /*<<< orphan*/  flags; } ;
struct mthca_dev {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTHCA_CMD_USE_EVENTS ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void mthca_cmd_use_polling(struct mthca_dev *dev)
{
	int i;

	dev->cmd.flags &= ~MTHCA_CMD_USE_EVENTS;

	for (i = 0; i < dev->cmd.max_cmds; ++i)
		down(&dev->cmd.event_sem);

	kfree(dev->cmd.context);

	up(&dev->cmd.poll_sem);
}