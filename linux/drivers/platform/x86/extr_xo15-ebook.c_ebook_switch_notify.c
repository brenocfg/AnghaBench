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
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
#define  ACPI_FIXED_HARDWARE_EVENT 129 
#define  XO15_EBOOK_NOTIFY_STATUS 128 
 int /*<<< orphan*/  ebook_send_state (struct acpi_device*) ; 

__attribute__((used)) static void ebook_switch_notify(struct acpi_device *device, u32 event)
{
	switch (event) {
	case ACPI_FIXED_HARDWARE_EVENT:
	case XO15_EBOOK_NOTIFY_STATUS:
		ebook_send_state(device);
		break;
	default:
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Unsupported event [0x%x]\n", event));
		break;
	}
}