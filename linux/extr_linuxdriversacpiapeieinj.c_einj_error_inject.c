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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int ACPI5_VENDOR_BIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IORESOURCE_SYSTEM_RAM ; 
 int /*<<< orphan*/  IORES_DESC_NONE ; 
 int /*<<< orphan*/  IORES_DESC_PERSISTENT_MEMORY ; 
 int MEM_ERROR_MASK ; 
 int PAGE_MASK ; 
 scalar_t__ REGION_INTERSECTS ; 
 int SETWA_FLAGS_APICID ; 
 int SETWA_FLAGS_MEM ; 
 int SETWA_FLAGS_PCIE_SBDF ; 
 int __einj_error_inject (int,int,int,int,int,int) ; 
 scalar_t__ acpi5 ; 
 int /*<<< orphan*/  einj_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ param_extension ; 
 scalar_t__ region_intersects (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vendor_flags ; 

__attribute__((used)) static int einj_error_inject(u32 type, u32 flags, u64 param1, u64 param2,
			     u64 param3, u64 param4)
{
	int rc;
	u64 base_addr, size;

	/* If user manually set "flags", make sure it is legal */
	if (flags && (flags &
		~(SETWA_FLAGS_APICID|SETWA_FLAGS_MEM|SETWA_FLAGS_PCIE_SBDF)))
		return -EINVAL;

	/*
	 * We need extra sanity checks for memory errors.
	 * Other types leap directly to injection.
	 */

	/* ensure param1/param2 existed */
	if (!(param_extension || acpi5))
		goto inject;

	/* ensure injection is memory related */
	if (type & ACPI5_VENDOR_BIT) {
		if (vendor_flags != SETWA_FLAGS_MEM)
			goto inject;
	} else if (!(type & MEM_ERROR_MASK) && !(flags & SETWA_FLAGS_MEM))
		goto inject;

	/*
	 * Disallow crazy address masks that give BIOS leeway to pick
	 * injection address almost anywhere. Insist on page or
	 * better granularity and that target address is normal RAM or
	 * NVDIMM.
	 */
	base_addr = param1 & param2;
	size = ~param2 + 1;

	if (((param2 & PAGE_MASK) != PAGE_MASK) ||
	    ((region_intersects(base_addr, size, IORESOURCE_SYSTEM_RAM, IORES_DESC_NONE)
				!= REGION_INTERSECTS) &&
	     (region_intersects(base_addr, size, IORESOURCE_MEM, IORES_DESC_PERSISTENT_MEMORY)
				!= REGION_INTERSECTS)))
		return -EINVAL;

inject:
	mutex_lock(&einj_mutex);
	rc = __einj_error_inject(type, flags, param1, param2, param3, param4);
	mutex_unlock(&einj_mutex);

	return rc;
}