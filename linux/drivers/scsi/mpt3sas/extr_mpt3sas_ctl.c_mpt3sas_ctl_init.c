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
typedef  int ushort ;

/* Variables and functions */
 int /*<<< orphan*/  MPT2SAS_DRIVER_NAME ; 
 int /*<<< orphan*/  MPT2SAS_MINOR ; 
 int /*<<< orphan*/  MPT3SAS_DRIVER_NAME ; 
 int /*<<< orphan*/  MPT3SAS_MINOR ; 
 int /*<<< orphan*/ * async_queue ; 
 int /*<<< orphan*/  ctl_dev ; 
 int /*<<< orphan*/  ctl_poll_wait ; 
 int /*<<< orphan*/  gen2_ctl_dev ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mpt3sas_ctl_init(ushort hbas_to_enumerate)
{
	async_queue = NULL;

	/* Don't register mpt3ctl ioctl device if
	 * hbas_to_enumarate is one.
	 */
	if (hbas_to_enumerate != 1)
		if (misc_register(&ctl_dev) < 0)
			pr_err("%s can't register misc device [minor=%d]\n",
			    MPT3SAS_DRIVER_NAME, MPT3SAS_MINOR);

	/* Don't register mpt3ctl ioctl device if
	 * hbas_to_enumarate is two.
	 */
	if (hbas_to_enumerate != 2)
		if (misc_register(&gen2_ctl_dev) < 0)
			pr_err("%s can't register misc device [minor=%d]\n",
			    MPT2SAS_DRIVER_NAME, MPT2SAS_MINOR);

	init_waitqueue_head(&ctl_poll_wait);
}