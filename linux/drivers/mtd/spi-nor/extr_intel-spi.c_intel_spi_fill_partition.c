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
struct mtd_partition {int size; char* name; } ;
struct intel_spi {int nregions; int writeable; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ FREG (int) ; 
 int FREG_BASE_MASK ; 
 int FREG_LIMIT_MASK ; 
 int FREG_LIMIT_SHIFT ; 
 scalar_t__ intel_spi_is_protected (struct intel_spi*,int,int) ; 
 int /*<<< orphan*/  memset (struct mtd_partition*,int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void intel_spi_fill_partition(struct intel_spi *ispi,
				     struct mtd_partition *part)
{
	u64 end;
	int i;

	memset(part, 0, sizeof(*part));

	/* Start from the mandatory descriptor region */
	part->size = 4096;
	part->name = "BIOS";

	/*
	 * Now try to find where this partition ends based on the flash
	 * region registers.
	 */
	for (i = 1; i < ispi->nregions; i++) {
		u32 region, base, limit;

		region = readl(ispi->base + FREG(i));
		base = region & FREG_BASE_MASK;
		limit = (region & FREG_LIMIT_MASK) >> FREG_LIMIT_SHIFT;

		if (base >= limit || limit == 0)
			continue;

		/*
		 * If any of the regions have protection bits set, make the
		 * whole partition read-only to be on the safe side.
		 */
		if (intel_spi_is_protected(ispi, base, limit))
			ispi->writeable = false;

		end = (limit << 12) + 4096;
		if (end > part->size)
			part->size = end;
	}
}