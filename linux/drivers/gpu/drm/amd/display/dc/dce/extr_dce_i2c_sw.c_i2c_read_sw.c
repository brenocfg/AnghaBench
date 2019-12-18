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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ddc {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_byte_sw (struct dc_context*,struct ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_byte_sw (struct dc_context*,struct ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i2c_read_sw(
	struct dc_context *ctx,
	struct ddc *ddc_handle,
	uint16_t clock_delay_div_4,
	uint8_t address,
	uint32_t length,
	uint8_t *data)
{
	uint32_t i = 0;

	if (!write_byte_sw(ctx, ddc_handle, clock_delay_div_4, address))
		return false;

	while (i < length) {
		if (!read_byte_sw(ctx, ddc_handle, clock_delay_div_4, data + i,
			i < length - 1))
			return false;
		++i;
	}

	return true;
}