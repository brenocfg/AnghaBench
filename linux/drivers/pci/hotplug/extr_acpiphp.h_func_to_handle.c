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
struct acpiphp_func {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 TYPE_1__* func_to_acpi_device (struct acpiphp_func*) ; 

__attribute__((used)) static inline acpi_handle func_to_handle(struct acpiphp_func *func)
{
	return func_to_acpi_device(func)->handle;
}