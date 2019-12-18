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
typedef  int phys_addr_t ;

/* Variables and functions */
 int GENMASK_ULL (int,int) ; 
 scalar_t__ GICR_PROPBASER ; 
 int /*<<< orphan*/  LPI_PROPBASE_SZ ; 
 int gic_check_reserved_range (int,int /*<<< orphan*/ ) ; 
 scalar_t__ gic_data_rdist_rd_base () ; 
 int gicr_read_propbaser (scalar_t__) ; 

__attribute__((used)) static bool enabled_lpis_allowed(void)
{
	phys_addr_t addr;
	u64 val;

	/* Check whether the property table is in a reserved region */
	val = gicr_read_propbaser(gic_data_rdist_rd_base() + GICR_PROPBASER);
	addr = val & GENMASK_ULL(51, 12);

	return gic_check_reserved_range(addr, LPI_PROPBASE_SZ);
}