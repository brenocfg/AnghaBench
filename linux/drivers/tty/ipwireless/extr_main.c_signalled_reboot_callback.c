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
struct ipw_dev {int /*<<< orphan*/  work_reboot; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void signalled_reboot_callback(void *callback_data)
{
	struct ipw_dev *ipw = (struct ipw_dev *) callback_data;

	/* Delegate to process context. */
	schedule_work(&ipw->work_reboot);
}