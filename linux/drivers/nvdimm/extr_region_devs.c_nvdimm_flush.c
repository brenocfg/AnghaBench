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
struct nd_region {scalar_t__ (* flush ) (struct nd_region*,struct bio*) ;} ;
struct bio {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int generic_nvdimm_flush (struct nd_region*) ; 
 scalar_t__ stub1 (struct nd_region*,struct bio*) ; 

int nvdimm_flush(struct nd_region *nd_region, struct bio *bio)
{
	int rc = 0;

	if (!nd_region->flush)
		rc = generic_nvdimm_flush(nd_region);
	else {
		if (nd_region->flush(nd_region, bio))
			rc = -EIO;
	}

	return rc;
}