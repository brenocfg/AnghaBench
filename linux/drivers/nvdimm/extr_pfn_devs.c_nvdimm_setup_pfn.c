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
struct nd_pfn {int /*<<< orphan*/  ndns; int /*<<< orphan*/  uuid; } ;
struct dev_pagemap {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int __nvdimm_setup_pfn (struct nd_pfn*,struct dev_pagemap*) ; 
 int nd_pfn_init (struct nd_pfn*) ; 

int nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
{
	int rc;

	if (!nd_pfn->uuid || !nd_pfn->ndns)
		return -ENODEV;

	rc = nd_pfn_init(nd_pfn);
	if (rc)
		return rc;

	/* we need a valid pfn_sb before we can init a dev_pagemap */
	return __nvdimm_setup_pfn(nd_pfn, pgmap);
}