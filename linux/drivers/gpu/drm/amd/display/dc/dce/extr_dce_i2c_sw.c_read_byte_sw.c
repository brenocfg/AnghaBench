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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct ddc {int dummy; } ;
struct dc_context {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCL ; 
 int /*<<< orphan*/  SDA ; 
 scalar_t__ read_bit_from_ddc (struct ddc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_for_scl_high_sw (struct dc_context*,struct ddc*,int) ; 
 int /*<<< orphan*/  write_bit_to_ddc (struct ddc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool read_byte_sw(
	struct dc_context *ctx,
	struct ddc *ddc_handle,
	uint16_t clock_delay_div_4,
	uint8_t *byte,
	bool more)
{
	int32_t shift = 7;

	uint8_t data = 0;

	/* The data bits are read from MSB to LSB;
	 * bit is read while SCL is high
	 */

	do {
		write_bit_to_ddc(ddc_handle, SCL, true);

		if (!wait_for_scl_high_sw(ctx, ddc_handle, clock_delay_div_4))
			return false;

		if (read_bit_from_ddc(ddc_handle, SDA))
			data |= (1 << shift);

		write_bit_to_ddc(ddc_handle, SCL, false);

		udelay(clock_delay_div_4 << 1);

		--shift;
	} while (shift >= 0);

	/* read only whole byte */

	*byte = data;

	udelay(clock_delay_div_4);

	/* send the acknowledge bit:
	 * SDA low means ACK, SDA high means NACK
	 */

	write_bit_to_ddc(ddc_handle, SDA, !more);

	udelay(clock_delay_div_4);

	write_bit_to_ddc(ddc_handle, SCL, true);

	if (!wait_for_scl_high_sw(ctx, ddc_handle, clock_delay_div_4))
		return false;

	write_bit_to_ddc(ddc_handle, SCL, false);

	udelay(clock_delay_div_4);

	write_bit_to_ddc(ddc_handle, SDA, true);

	udelay(clock_delay_div_4);

	return true;
}