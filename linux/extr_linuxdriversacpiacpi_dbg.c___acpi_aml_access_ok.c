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
struct TYPE_2__ {int flags; scalar_t__ thread; } ;

/* Variables and functions */
 int ACPI_AML_CLOSED ; 
 unsigned long ACPI_AML_KERN ; 
 int ACPI_AML_OPENED ; 
 int /*<<< orphan*/  __acpi_aml_running () ; 
 TYPE_1__ acpi_aml_io ; 
 scalar_t__ current ; 

__attribute__((used)) static inline bool __acpi_aml_access_ok(unsigned long flag)
{
	/*
	 * The debugger interface is in opened state (OPENED && !CLOSED),
	 * then it is allowed to access the debugger buffers from either
	 * user space or the kernel space.
	 * In addition, for the kernel space, only the debugger thread
	 * (thread ID matched) is allowed to access.
	 */
	if (!(acpi_aml_io.flags & ACPI_AML_OPENED) ||
	    (acpi_aml_io.flags & ACPI_AML_CLOSED) ||
	    !__acpi_aml_running())
		return false;
	if ((flag & ACPI_AML_KERN) &&
	    current != acpi_aml_io.thread)
		return false;
	return true;
}