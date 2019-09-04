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
struct acpi_ec_query {scalar_t__ handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ec_put_query_handler (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct acpi_ec_query*) ; 

__attribute__((used)) static void acpi_ec_delete_query(struct acpi_ec_query *q)
{
	if (q) {
		if (q->handler)
			acpi_ec_put_query_handler(q->handler);
		kfree(q);
	}
}