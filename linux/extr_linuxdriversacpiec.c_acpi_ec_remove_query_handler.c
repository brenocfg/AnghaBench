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
typedef  int /*<<< orphan*/  u8 ;
struct acpi_ec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ec_remove_query_handlers (struct acpi_ec*,int,int /*<<< orphan*/ ) ; 

void acpi_ec_remove_query_handler(struct acpi_ec *ec, u8 query_bit)
{
	acpi_ec_remove_query_handlers(ec, false, query_bit);
}