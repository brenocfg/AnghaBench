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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  ACPI_UINT64_MAX ; 
 int /*<<< orphan*/  AE_NUMERIC_OVERFLOW ; 
 int /*<<< orphan*/  AE_OK ; 
 int acpi_gbl_integer_bit_width ; 
 int /*<<< orphan*/  acpi_ut_short_divide (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status
acpi_ut_strtoul_multiply64(u64 multiplicand, u32 base, u64 *out_product)
{
	u64 product;
	u64 quotient;

	/* Exit if either operand is zero */

	*out_product = 0;
	if (!multiplicand || !base) {
		return (AE_OK);
	}

	/*
	 * Check for 64-bit overflow before the actual multiplication.
	 *
	 * Notes: 64-bit division is often not supported on 32-bit platforms
	 * (it requires a library function), Therefore ACPICA has a local
	 * 64-bit divide function. Also, Multiplier is currently only used
	 * as the radix (8/10/16), to the 64/32 divide will always work.
	 */
	acpi_ut_short_divide(ACPI_UINT64_MAX, base, &quotient, NULL);
	if (multiplicand > quotient) {
		return (AE_NUMERIC_OVERFLOW);
	}

	product = multiplicand * base;

	/* Check for 32-bit overflow if necessary */

	if ((acpi_gbl_integer_bit_width == 32) && (product > ACPI_UINT32_MAX)) {
		return (AE_NUMERIC_OVERFLOW);
	}

	*out_product = product;
	return (AE_OK);
}