#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct TYPE_4__ {int recvd_hw_ready; int /*<<< orphan*/  devc; int /*<<< orphan*/  wait_hw_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMEOUT_FOR_HW_RDY_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ish_fw_reset_handler (TYPE_1__*) ; 
 TYPE_1__* ishtp_dev ; 
 int /*<<< orphan*/  ishtp_reset_compl_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fw_reset_work_fn(struct work_struct *unused)
{
	int	rv;

	rv = ish_fw_reset_handler(ishtp_dev);
	if (!rv) {
		/* ISH is ILUP & ISHTP-ready. Restart ISHTP */
		msleep_interruptible(TIMEOUT_FOR_HW_RDY_MS);
		ishtp_dev->recvd_hw_ready = 1;
		wake_up_interruptible(&ishtp_dev->wait_hw_ready);

		/* ISHTP notification in IPC_RESET sequence completion */
		ishtp_reset_compl_handler(ishtp_dev);
	} else
		dev_err(ishtp_dev->devc, "[ishtp-ish]: FW reset failed (%d)\n",
			rv);
}