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
struct TYPE_2__ {scalar_t__ lo; scalar_t__ hi; } ;
union uint64_overlay {int /*<<< orphan*/  full; TYPE_1__ part; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SHIFT_LEFT_64_BY_32 (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_short_shift_left ; 

acpi_status acpi_ut_short_shift_left(u64 operand, u32 count, u64 *out_result)
{
	union uint64_overlay operand_ovl;

	ACPI_FUNCTION_TRACE(ut_short_shift_left);

	operand_ovl.full = operand;

	if ((count & 63) >= 32) {
		operand_ovl.part.hi = operand_ovl.part.lo;
		operand_ovl.part.lo = 0;
		count = (count & 63) - 32;
	}
	ACPI_SHIFT_LEFT_64_BY_32(operand_ovl.part.hi,
				 operand_ovl.part.lo, count);

	/* Return only what was requested */

	if (out_result) {
		*out_result = operand_ovl.full;
	}

	return_ACPI_STATUS(AE_OK);
}