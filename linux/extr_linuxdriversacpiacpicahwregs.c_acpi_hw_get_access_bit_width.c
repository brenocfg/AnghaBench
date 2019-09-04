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
typedef  int u8 ;
typedef  int u64 ;
struct acpi_generic_address {int bit_offset; int bit_width; scalar_t__ space_id; scalar_t__ access_width; } ;

/* Variables and functions */
 int ACPI_ACCESS_BIT_WIDTH (scalar_t__) ; 
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_IO ; 
 scalar_t__ ACPI_IS_ALIGNED (int,int) ; 
 scalar_t__ ACPI_IS_POWER_OF_TWO (int) ; 
 int ACPI_ROUND_UP_POWER_OF_TWO_8 (int) ; 

__attribute__((used)) static u8
acpi_hw_get_access_bit_width(u64 address,
			     struct acpi_generic_address *reg, u8 max_bit_width)
{
	u8 access_bit_width;

	/*
	 * GAS format "register", used by FADT:
	 *  1. Detected if bit_offset is 0 and bit_width is 8/16/32/64;
	 *  2. access_size field is ignored and bit_width field is used for
	 *     determining the boundary of the IO accesses.
	 * GAS format "region", used by APEI registers:
	 *  1. Detected if bit_offset is not 0 or bit_width is not 8/16/32/64;
	 *  2. access_size field is used for determining the boundary of the
	 *     IO accesses;
	 *  3. bit_offset/bit_width fields are used to describe the "region".
	 *
	 * Note: This algorithm assumes that the "Address" fields should always
	 *       contain aligned values.
	 */
	if (!reg->bit_offset && reg->bit_width &&
	    ACPI_IS_POWER_OF_TWO(reg->bit_width) &&
	    ACPI_IS_ALIGNED(reg->bit_width, 8)) {
		access_bit_width = reg->bit_width;
	} else if (reg->access_width) {
		access_bit_width = ACPI_ACCESS_BIT_WIDTH(reg->access_width);
	} else {
		access_bit_width =
		    ACPI_ROUND_UP_POWER_OF_TWO_8(reg->bit_offset +
						 reg->bit_width);
		if (access_bit_width <= 8) {
			access_bit_width = 8;
		} else {
			while (!ACPI_IS_ALIGNED(address, access_bit_width >> 3)) {
				access_bit_width >>= 1;
			}
		}
	}

	/* Maximum IO port access bit width is 32 */

	if (reg->space_id == ACPI_ADR_SPACE_SYSTEM_IO) {
		max_bit_width = 32;
	}

	/*
	 * Return access width according to the requested maximum access bit width,
	 * as the caller should know the format of the register and may enforce
	 * a 32-bit accesses.
	 */
	if (access_bit_width < max_bit_width) {
		return (access_bit_width);
	}
	return (max_bit_width);
}