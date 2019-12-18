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
typedef  scalar_t__ uint16_t ;
struct ddc {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ I2C_SW_TIMEOUT_DELAY ; 
 int /*<<< orphan*/  SCL ; 
 scalar_t__ read_bit_from_ddc (struct ddc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static bool wait_for_scl_high_sw(
	struct dc_context *ctx,
	struct ddc *ddc,
	uint16_t clock_delay_div_4)
{
	uint32_t scl_retry = 0;
	uint32_t scl_retry_max = I2C_SW_TIMEOUT_DELAY / clock_delay_div_4;

	udelay(clock_delay_div_4);

	do {
		if (read_bit_from_ddc(ddc, SCL))
			return true;

		udelay(clock_delay_div_4);

		++scl_retry;
	} while (scl_retry <= scl_retry_max);

	return false;
}