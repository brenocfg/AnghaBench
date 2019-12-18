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
struct TYPE_2__ {int /*<<< orphan*/  (* unmap_frames ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XENFEAT_auto_translated_physmap ; 
 TYPE_1__* gnttab_interface ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  xen_feature (int /*<<< orphan*/ ) ; 

int gnttab_suspend(void)
{
	if (!xen_feature(XENFEAT_auto_translated_physmap))
		gnttab_interface->unmap_frames();
	return 0;
}