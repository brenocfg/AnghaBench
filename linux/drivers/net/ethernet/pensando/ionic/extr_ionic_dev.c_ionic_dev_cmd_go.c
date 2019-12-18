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
typedef  union ionic_dev_cmd {int dummy; } ionic_dev_cmd ;
struct ionic_dev {TYPE_1__* dev_cmd_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  doorbell; int /*<<< orphan*/  done; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,union ionic_dev_cmd*,int) ; 

void ionic_dev_cmd_go(struct ionic_dev *idev, union ionic_dev_cmd *cmd)
{
	memcpy_toio(&idev->dev_cmd_regs->cmd, cmd, sizeof(*cmd));
	iowrite32(0, &idev->dev_cmd_regs->done);
	iowrite32(1, &idev->dev_cmd_regs->doorbell);
}