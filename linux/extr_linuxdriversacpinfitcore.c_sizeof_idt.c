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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int length; } ;
struct acpi_nfit_interleave {int line_count; TYPE_1__ header; } ;

/* Variables and functions */

__attribute__((used)) static size_t sizeof_idt(struct acpi_nfit_interleave *idt)
{
	if (idt->header.length < sizeof(*idt))
		return 0;
	return sizeof(*idt) + sizeof(u32) * (idt->line_count - 1);
}