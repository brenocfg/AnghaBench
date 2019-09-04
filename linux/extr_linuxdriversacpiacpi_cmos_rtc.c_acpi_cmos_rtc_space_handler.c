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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_READ ; 
 scalar_t__ ACPI_WRITE ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  CMOS_READ (int) ; 
 int /*<<< orphan*/  CMOS_WRITE (int /*<<< orphan*/ ,int) ; 
 int DIV_ROUND_UP (scalar_t__,int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status
acpi_cmos_rtc_space_handler(u32 function, acpi_physical_address address,
		      u32 bits, u64 *value64,
		      void *handler_context, void *region_context)
{
	int i;
	u8 *value = (u8 *)value64;

	if (address > 0xff || !value64)
		return AE_BAD_PARAMETER;

	if (function != ACPI_WRITE && function != ACPI_READ)
		return AE_BAD_PARAMETER;

	spin_lock_irq(&rtc_lock);

	for (i = 0; i < DIV_ROUND_UP(bits, 8); ++i, ++address, ++value)
		if (function == ACPI_READ)
			*value = CMOS_READ(address);
		else
			CMOS_WRITE(*value, address);

	spin_unlock_irq(&rtc_lock);

	return AE_OK;
}