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
struct ipmi_smi {int /*<<< orphan*/ * null_user_handler; int /*<<< orphan*/  waitq; struct bmc_device* bmc; } ;
struct bmc_device {int dyn_guid_set; } ;

/* Variables and functions */
 int /*<<< orphan*/ * guid_handler ; 
 int send_guid_cmd (struct ipmi_smi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __get_guid(struct ipmi_smi *intf)
{
	int rv;
	struct bmc_device *bmc = intf->bmc;

	bmc->dyn_guid_set = 2;
	intf->null_user_handler = guid_handler;
	rv = send_guid_cmd(intf, 0);
	if (rv)
		/* Send failed, no GUID available. */
		bmc->dyn_guid_set = 0;

	wait_event(intf->waitq, bmc->dyn_guid_set != 2);

	/* dyn_guid_set makes the guid data available. */
	smp_rmb();

	intf->null_user_handler = NULL;
}