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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ddc {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ I2C_SW_RETRIES ; 
 int /*<<< orphan*/  SCL ; 
 int /*<<< orphan*/  SDA ; 
 int /*<<< orphan*/  read_bit_from_ddc (struct ddc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_scl_high_sw (struct dc_context*,struct ddc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_bit_to_ddc (struct ddc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool start_sync_sw(
	struct dc_context *ctx,
	struct ddc *ddc_handle,
	uint16_t clock_delay_div_4)
{
	uint32_t retry = 0;

	/* The I2C communications start signal is:
	 * the SDA going low from high, while the SCL is high.
	 */

	write_bit_to_ddc(ddc_handle, SCL, true);

	udelay(clock_delay_div_4);

	do {
		write_bit_to_ddc(ddc_handle, SDA, true);

		if (!read_bit_from_ddc(ddc_handle, SDA)) {
			++retry;
			continue;
		}

		udelay(clock_delay_div_4);

		write_bit_to_ddc(ddc_handle, SCL, true);

		if (!wait_for_scl_high_sw(ctx, ddc_handle, clock_delay_div_4))
			break;

		write_bit_to_ddc(ddc_handle, SDA, false);

		udelay(clock_delay_div_4);

		write_bit_to_ddc(ddc_handle, SCL, false);

		udelay(clock_delay_div_4);

		return true;
	} while (retry <= I2C_SW_RETRIES);

	return false;
}