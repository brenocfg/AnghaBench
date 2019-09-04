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

/* Variables and functions */
 int /*<<< orphan*/  H_GET_24X7_CATALOG_PAGE ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static long h_get_24x7_catalog_page_(unsigned long phys_4096,
				     unsigned long version, unsigned long index)
{
	pr_devel("h_get_24x7_catalog_page(0x%lx, %lu, %lu)",
			phys_4096, version, index);

	WARN_ON(!IS_ALIGNED(phys_4096, 4096));

	return plpar_hcall_norets(H_GET_24X7_CATALOG_PAGE,
			phys_4096, version, index);
}