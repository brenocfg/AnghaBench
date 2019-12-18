#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acpiphp_func {int dummy; } ;
struct acpi_device {int dummy; } ;
struct TYPE_3__ {struct acpi_device* self; } ;
struct TYPE_4__ {TYPE_1__ hp; } ;

/* Variables and functions */
 TYPE_2__* func_to_context (struct acpiphp_func*) ; 

__attribute__((used)) static inline struct acpi_device *func_to_acpi_device(struct acpiphp_func *func)
{
	return func_to_context(func)->hp.self;
}