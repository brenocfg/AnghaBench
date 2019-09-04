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
struct capi_ctr {TYPE_1__* driverdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  ncci_head; } ;
typedef  TYPE_1__ hycapictrl_info ;

/* Variables and functions */
 int /*<<< orphan*/  capi_ctr_down (struct capi_ctr*) ; 
 int /*<<< orphan*/  capilib_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hycapi_reset_ctr(struct capi_ctr *ctrl)
{
	hycapictrl_info *cinfo = ctrl->driverdata;

#ifdef HYCAPI_PRINTFNAMES
	printk(KERN_NOTICE "HYCAPI hycapi_reset_ctr\n");
#endif
	capilib_release(&cinfo->ncci_head);
	capi_ctr_down(ctrl);
}