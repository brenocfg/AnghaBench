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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  gpe; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_set_gpe_wake_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec_no_wakeup ; 
 TYPE_1__* first_ec ; 

void acpi_ec_set_gpe_wake_mask(u8 action)
{
	if (first_ec && !ec_no_wakeup)
		acpi_set_gpe_wake_mask(NULL, first_ec->gpe, action);
}