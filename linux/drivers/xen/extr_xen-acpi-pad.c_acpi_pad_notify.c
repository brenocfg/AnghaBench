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
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
#define  ACPI_PROCESSOR_AGGREGATOR_NOTIFY 128 
 int /*<<< orphan*/  acpi_pad_handle_notify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static void acpi_pad_notify(acpi_handle handle, u32 event,
	void *data)
{
	switch (event) {
	case ACPI_PROCESSOR_AGGREGATOR_NOTIFY:
		acpi_pad_handle_notify(handle);
		break;
	default:
		pr_warn("Unsupported event [0x%x]\n", event);
		break;
	}
}