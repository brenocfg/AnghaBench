#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t grant_ref_t ;
typedef  int /*<<< orphan*/  domid_t ;
struct TYPE_4__ {TYPE_1__* v1; } ;
struct TYPE_3__ {unsigned long frame; unsigned int flags; int /*<<< orphan*/  domid; } ;

/* Variables and functions */
 TYPE_2__ gnttab_shared ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void gnttab_update_entry_v1(grant_ref_t ref, domid_t domid,
				   unsigned long frame, unsigned flags)
{
	gnttab_shared.v1[ref].domid = domid;
	gnttab_shared.v1[ref].frame = frame;
	wmb();
	gnttab_shared.v1[ref].flags = flags;
}