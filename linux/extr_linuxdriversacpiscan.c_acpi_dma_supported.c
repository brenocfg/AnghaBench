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
struct TYPE_2__ {scalar_t__ cca_seen; } ;
struct acpi_device {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ACPI_CCA_REQUIRED ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 

bool acpi_dma_supported(struct acpi_device *adev)
{
	if (!adev)
		return false;

	if (adev->flags.cca_seen)
		return true;

	/*
	* Per ACPI 6.0 sec 6.2.17, assume devices can do cache-coherent
	* DMA on "Intel platforms".  Presumably that includes all x86 and
	* ia64, and other arches will set CONFIG_ACPI_CCA_REQUIRED=y.
	*/
	if (!IS_ENABLED(CONFIG_ACPI_CCA_REQUIRED))
		return true;

	return false;
}