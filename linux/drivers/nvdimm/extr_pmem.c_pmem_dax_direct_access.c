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
struct pmem_device {int dummy; } ;
struct dax_device {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 long __pmem_direct_access (struct pmem_device*,int /*<<< orphan*/ ,long,void**,int /*<<< orphan*/ *) ; 
 struct pmem_device* dax_get_private (struct dax_device*) ; 

__attribute__((used)) static long pmem_dax_direct_access(struct dax_device *dax_dev,
		pgoff_t pgoff, long nr_pages, void **kaddr, pfn_t *pfn)
{
	struct pmem_device *pmem = dax_get_private(dax_dev);

	return __pmem_direct_access(pmem, pgoff, nr_pages, kaddr, pfn);
}