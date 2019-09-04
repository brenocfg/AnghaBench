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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_GPE0_BLK ; 
 int /*<<< orphan*/  ACPI_PM_EVT_BLK ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_hw_clear_status(void)
{
	u16 value;

	/* PMStatus: Clear WakeStatus/PwrBtnStatus */
	value = inw(ACPI_PM_EVT_BLK);
	value |= (1 << 8 | 1 << 15);
	outw(value, ACPI_PM_EVT_BLK);

	/* GPEStatus: Clear all generated events */
	outl(inl(ACPI_GPE0_BLK), ACPI_GPE0_BLK);
}