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
struct asus_laptop {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 char* METHOD_PEGA_DISABLE ; 
 char* METHOD_PEGA_ENABLE ; 
 int write_acpi_int (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int asus_pega_lucid_set(struct asus_laptop *asus, int unit, bool enable)
{
	char *method = enable ? METHOD_PEGA_ENABLE : METHOD_PEGA_DISABLE;
	return write_acpi_int(asus->handle, method, unit);
}