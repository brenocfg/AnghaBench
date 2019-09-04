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
struct mtip_port {TYPE_1__* dd; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int /*<<< orphan*/  MTIP_PF_ISSUE_CMDS_BIT ; 
 int /*<<< orphan*/  MTIP_PF_SVC_THD_ACTIVE_BIT ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ mtip_check_surprise_removal (int /*<<< orphan*/ ) ; 
 int mtip_commands_active (struct mtip_port*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int mtip_quiesce_io(struct mtip_port *port, unsigned long timeout)
{
	unsigned long to;
	bool active = true;

	blk_mq_quiesce_queue(port->dd->queue);

	to = jiffies + msecs_to_jiffies(timeout);
	do {
		if (test_bit(MTIP_PF_SVC_THD_ACTIVE_BIT, &port->flags) &&
			test_bit(MTIP_PF_ISSUE_CMDS_BIT, &port->flags)) {
			msleep(20);
			continue; /* svc thd is actively issuing commands */
		}

		msleep(100);

		if (mtip_check_surprise_removal(port->dd->pdev))
			goto err_fault;

		active = mtip_commands_active(port);
		if (!active)
			break;
	} while (time_before(jiffies, to));

	blk_mq_unquiesce_queue(port->dd->queue);
	return active ? -EBUSY : 0;
err_fault:
	blk_mq_unquiesce_queue(port->dd->queue);
	return -EFAULT;
}