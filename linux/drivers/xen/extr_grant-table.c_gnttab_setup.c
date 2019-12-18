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
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * vaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  XENFEAT_auto_translated_physmap ; 
 int gnttab_map (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int gnttab_max_grant_frames () ; 
 TYPE_2__ gnttab_shared ; 
 unsigned int nr_grant_frames ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 TYPE_1__ xen_auto_xlat_grant_frames ; 
 scalar_t__ xen_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gnttab_setup(void)
{
	unsigned int max_nr_gframes;

	max_nr_gframes = gnttab_max_grant_frames();
	if (max_nr_gframes < nr_grant_frames)
		return -ENOSYS;

	if (xen_feature(XENFEAT_auto_translated_physmap) && gnttab_shared.addr == NULL) {
		gnttab_shared.addr = xen_auto_xlat_grant_frames.vaddr;
		if (gnttab_shared.addr == NULL) {
			pr_warn("gnttab share frames is not mapped!\n");
			return -ENOMEM;
		}
	}
	return gnttab_map(0, nr_grant_frames - 1);
}