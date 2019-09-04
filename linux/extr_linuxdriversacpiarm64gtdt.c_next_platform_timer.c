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
struct acpi_gtdt_header {int /*<<< orphan*/  length; } ;
struct TYPE_2__ {void* gtdt_end; } ;

/* Variables and functions */
 TYPE_1__ acpi_gtdt_desc ; 

__attribute__((used)) static inline void *next_platform_timer(void *platform_timer)
{
	struct acpi_gtdt_header *gh = platform_timer;

	platform_timer += gh->length;
	if (platform_timer < acpi_gtdt_desc.gtdt_end)
		return platform_timer;

	return NULL;
}