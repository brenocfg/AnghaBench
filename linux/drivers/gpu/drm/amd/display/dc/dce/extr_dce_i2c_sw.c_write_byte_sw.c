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
 int /*<<< orphan*/  read_bit_from_ddc (struct ddc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_for_scl_high_sw (struct dc_context*,struct ddc*,int) ; 
 int /*<<< orphan*/  write_bit_to_ddc (struct ddc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool write_byte_sw(
	struct dc_context *ctx,
	struct ddc *ddc_handle,
	uint16_t clock_delay_div_4,
	uint8_t byte)
{
	int32_t shift = 7;
	bool ack;

	/* bits are transmitted serially, starting from MSB */

	do {
		udelay(clock_delay_div_4);

		write_bit_to_ddc(ddc_handle, SDA, (byte >> shift) & 1);

		udelay(clock_delay_div_4);

		write_bit_to_ddc(ddc_handle, SCL, true);

		if (!wait_for_scl_high_sw(ctx, ddc_handle, clock_delay_div_4))
			return false;

		write_bit_to_ddc(ddc_handle, SCL, false);

		--shift;
	} while (shift >= 0);

	/* The display sends ACK by preventing the SDA from going high
	 * after the SCL pulse we use to send our last data bit.
	 * If the SDA goes high after that bit, it's a NACK
	 */

	udelay(clock_delay_div_4);

	write_bit_to_ddc(ddc_handle, SDA, true);

	udelay(clock_delay_div_4);

	write_bit_to_ddc(ddc_handle, SCL, true);

	if (!wait_for_scl_high_sw(ctx, ddc_handle, clock_delay_div_4))
		return false;

	/* read ACK bit */

	ack = !read_bit_from_ddc(ddc_handle, SDA);

	udelay(clock_delay_div_4 << 1);

	write_bit_to_ddc(ddc_handle, SCL, false);

	udelay(clock_delay_div_4 << 1);

	return ack;
}