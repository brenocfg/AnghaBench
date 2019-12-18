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
typedef  void* u32 ;
struct intel_opregion {TYPE_1__* acpi; } ;
struct TYPE_2__ {void** did2; void** didl; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static void set_did(struct intel_opregion *opregion, int i, u32 val)
{
	if (i < ARRAY_SIZE(opregion->acpi->didl)) {
		opregion->acpi->didl[i] = val;
	} else {
		i -= ARRAY_SIZE(opregion->acpi->didl);

		if (WARN_ON(i >= ARRAY_SIZE(opregion->acpi->did2)))
			return;

		opregion->acpi->did2[i] = val;
	}
}