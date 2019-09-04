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
struct hfi1_pportdata {scalar_t__ qsfp_retry_count; int /*<<< orphan*/  start_link_work; int /*<<< orphan*/  link_wq; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 scalar_t__ MAX_QSFP_RETRIES ; 
 int /*<<< orphan*/  QSFP_RETRY_WAIT ; 
 int /*<<< orphan*/  dd_dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dd_dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_link (struct hfi1_pportdata*) ; 
 scalar_t__ test_qsfp_read (struct hfi1_pportdata*) ; 

__attribute__((used)) static void try_start_link(struct hfi1_pportdata *ppd)
{
	if (test_qsfp_read(ppd)) {
		/* read failed */
		if (ppd->qsfp_retry_count >= MAX_QSFP_RETRIES) {
			dd_dev_err(ppd->dd, "QSFP not responding, giving up\n");
			return;
		}
		dd_dev_info(ppd->dd,
			    "QSFP not responding, waiting and retrying %d\n",
			    (int)ppd->qsfp_retry_count);
		ppd->qsfp_retry_count++;
		queue_delayed_work(ppd->link_wq, &ppd->start_link_work,
				   msecs_to_jiffies(QSFP_RETRY_WAIT));
		return;
	}
	ppd->qsfp_retry_count = 0;

	start_link(ppd);
}