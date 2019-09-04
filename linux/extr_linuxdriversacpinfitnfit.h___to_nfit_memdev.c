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
struct nfit_mem {struct acpi_nfit_memory_map* memdev_pmem; struct acpi_nfit_memory_map* memdev_dcr; } ;
struct acpi_nfit_memory_map {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct acpi_nfit_memory_map *__to_nfit_memdev(
		struct nfit_mem *nfit_mem)
{
	if (nfit_mem->memdev_dcr)
		return nfit_mem->memdev_dcr;
	return nfit_mem->memdev_pmem;
}