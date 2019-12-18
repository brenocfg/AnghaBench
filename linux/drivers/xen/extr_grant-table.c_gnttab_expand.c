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
struct TYPE_2__ {unsigned int grefs_per_grant_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  gnttab_free_count ; 
 TYPE_1__* gnttab_interface ; 
 int gnttab_map (unsigned int,unsigned int) ; 
 unsigned int gnttab_max_grant_frames () ; 
 int grow_gnttab_list (unsigned int) ; 
 unsigned int nr_grant_frames ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int gnttab_expand(unsigned int req_entries)
{
	int rc;
	unsigned int cur, extra;

	BUG_ON(gnttab_interface == NULL);
	cur = nr_grant_frames;
	extra = ((req_entries + gnttab_interface->grefs_per_grant_frame - 1) /
		 gnttab_interface->grefs_per_grant_frame);
	if (cur + extra > gnttab_max_grant_frames()) {
		pr_warn_ratelimited("xen/grant-table: max_grant_frames reached"
				    " cur=%u extra=%u limit=%u"
				    " gnttab_free_count=%u req_entries=%u\n",
				    cur, extra, gnttab_max_grant_frames(),
				    gnttab_free_count, req_entries);
		return -ENOSPC;
	}

	rc = gnttab_map(cur, cur + extra - 1);
	if (rc == 0)
		rc = grow_gnttab_list(extra);

	return rc;
}