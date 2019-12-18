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
struct mxc_nand_host {int /*<<< orphan*/  dev; TYPE_1__* devtype_data; int /*<<< orphan*/  op_completion; } ;
struct TYPE_2__ {int (* check_int ) (struct mxc_nand_host*) ;} ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  irq_control (struct mxc_nand_host*,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (struct mxc_nand_host*) ; 
 int stub2 (struct mxc_nand_host*) ; 
 int stub3 (struct mxc_nand_host*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_op_done(struct mxc_nand_host *host, int useirq)
{
	int ret = 0;

	/*
	 * If operation is already complete, don't bother to setup an irq or a
	 * loop.
	 */
	if (host->devtype_data->check_int(host))
		return 0;

	if (useirq) {
		unsigned long timeout;

		reinit_completion(&host->op_completion);

		irq_control(host, 1);

		timeout = wait_for_completion_timeout(&host->op_completion, HZ);
		if (!timeout && !host->devtype_data->check_int(host)) {
			dev_dbg(host->dev, "timeout waiting for irq\n");
			ret = -ETIMEDOUT;
		}
	} else {
		int max_retries = 8000;
		int done;

		do {
			udelay(1);

			done = host->devtype_data->check_int(host);
			if (done)
				break;

		} while (--max_retries);

		if (!done) {
			dev_dbg(host->dev, "timeout polling for completion\n");
			ret = -ETIMEDOUT;
		}
	}

	WARN_ONCE(ret < 0, "timeout! useirq=%d\n", useirq);

	return ret;
}