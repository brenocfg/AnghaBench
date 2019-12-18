#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xencons_info {int vtermno; int /*<<< orphan*/  list; int /*<<< orphan*/  intf; int /*<<< orphan*/  evtchn; } ;
struct TYPE_4__ {int /*<<< orphan*/  mfn; int /*<<< orphan*/  evtchn; } ;
struct TYPE_5__ {TYPE_1__ domU; } ;
struct TYPE_6__ {TYPE_2__ console; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfn_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* xen_start_info ; 
 int /*<<< orphan*/  xenconsoles ; 

__attribute__((used)) static int xencons_info_pv_init(struct xencons_info *info, int vtermno)
{
	info->evtchn = xen_start_info->console.domU.evtchn;
	/* GFN == MFN for PV guest */
	info->intf = gfn_to_virt(xen_start_info->console.domU.mfn);
	info->vtermno = vtermno;

	list_add_tail(&info->list, &xenconsoles);

	return 0;
}