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
struct TYPE_2__ {int /*<<< orphan*/  gpe; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_dispatch_gpe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* first_ec ; 

void acpi_ec_dispatch_gpe(void)
{
	if (first_ec)
		acpi_dispatch_gpe(NULL, first_ec->gpe);
}