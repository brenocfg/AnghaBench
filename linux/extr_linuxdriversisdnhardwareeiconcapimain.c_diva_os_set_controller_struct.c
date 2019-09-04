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
struct capi_ctr {int /*<<< orphan*/  owner; int /*<<< orphan*/  proc_show; int /*<<< orphan*/ * reset_ctr; int /*<<< orphan*/ * load_firmware; int /*<<< orphan*/  driver_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVERLNAME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  diva_ctl_proc_show ; 

void diva_os_set_controller_struct(struct capi_ctr *ctrl)
{
	ctrl->driver_name = DRIVERLNAME;
	ctrl->load_firmware = NULL;
	ctrl->reset_ctr = NULL;
	ctrl->proc_show = diva_ctl_proc_show;
	ctrl->owner = THIS_MODULE;
}