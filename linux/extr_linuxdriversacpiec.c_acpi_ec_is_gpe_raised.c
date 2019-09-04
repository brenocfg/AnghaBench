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
struct acpi_ec {int /*<<< orphan*/  gpe; } ;
typedef  int acpi_event_status ;

/* Variables and functions */
 int ACPI_EVENT_FLAG_STATUS_SET ; 
 int /*<<< orphan*/  acpi_get_gpe_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline bool acpi_ec_is_gpe_raised(struct acpi_ec *ec)
{
	acpi_event_status gpe_status = 0;

	(void)acpi_get_gpe_status(NULL, ec->gpe, &gpe_status);
	return (gpe_status & ACPI_EVENT_FLAG_STATUS_SET) ? true : false;
}