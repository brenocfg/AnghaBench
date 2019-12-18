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
typedef  void* acpi_handle ;

/* Variables and functions */
 int write_acpi_int (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int eeepc_rfkill_set(void *data, bool blocked)
{
	acpi_handle handle = data;

	return write_acpi_int(handle, NULL, !blocked);
}