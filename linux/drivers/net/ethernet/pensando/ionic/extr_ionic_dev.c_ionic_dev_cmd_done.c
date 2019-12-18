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
struct ionic_dev {TYPE_1__* dev_cmd_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int IONIC_DEV_CMD_DONE ; 
 int ioread32 (int /*<<< orphan*/ *) ; 

bool ionic_dev_cmd_done(struct ionic_dev *idev)
{
	return ioread32(&idev->dev_cmd_regs->done) & IONIC_DEV_CMD_DONE;
}