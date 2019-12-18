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
struct nd_region_data {int dummy; } ;
struct nd_region {int ndr_mappings; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 struct nd_region_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_idx ; 
 int /*<<< orphan*/  hash_32 (scalar_t__,int) ; 
 scalar_t__ ndrd_get_flush_wpq (struct nd_region_data*,int,int) ; 
 int this_cpu_add_return (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

int generic_nvdimm_flush(struct nd_region *nd_region)
{
	struct nd_region_data *ndrd = dev_get_drvdata(&nd_region->dev);
	int i, idx;

	/*
	 * Try to encourage some diversity in flush hint addresses
	 * across cpus assuming a limited number of flush hints.
	 */
	idx = this_cpu_read(flush_idx);
	idx = this_cpu_add_return(flush_idx, hash_32(current->pid + idx, 8));

	/*
	 * The first wmb() is needed to 'sfence' all previous writes
	 * such that they are architecturally visible for the platform
	 * buffer flush.  Note that we've already arranged for pmem
	 * writes to avoid the cache via memcpy_flushcache().  The final
	 * wmb() ensures ordering for the NVDIMM flush write.
	 */
	wmb();
	for (i = 0; i < nd_region->ndr_mappings; i++)
		if (ndrd_get_flush_wpq(ndrd, i, 0))
			writeq(1, ndrd_get_flush_wpq(ndrd, i, idx));
	wmb();

	return 0;
}