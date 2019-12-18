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
struct dc_context {int /*<<< orphan*/  dce_environment; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  DC_LOG_DC (char*,unsigned int,char const*,int) ; 
 int /*<<< orphan*/  DC_LOG_WARNING (char*,unsigned int,unsigned int,char const*,int) ; 
 int /*<<< orphan*/  IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 scalar_t__ dm_read_reg (struct dc_context const*,scalar_t__) ; 
 scalar_t__ get_reg_field_value_ex (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 

void generic_reg_wait(const struct dc_context *ctx,
	uint32_t addr, uint32_t shift, uint32_t mask, uint32_t condition_value,
	unsigned int delay_between_poll_us, unsigned int time_out_num_tries,
	const char *func_name, int line)
{
	uint32_t field_value;
	uint32_t reg_val;
	int i;

	/* something is terribly wrong if time out is > 200ms. (5Hz) */
	ASSERT(delay_between_poll_us * time_out_num_tries <= 3000000);

	for (i = 0; i <= time_out_num_tries; i++) {
		if (i) {
			if (delay_between_poll_us >= 1000)
				msleep(delay_between_poll_us/1000);
			else if (delay_between_poll_us > 0)
				udelay(delay_between_poll_us);
		}

		reg_val = dm_read_reg(ctx, addr);

		field_value = get_reg_field_value_ex(reg_val, mask, shift);

		if (field_value == condition_value) {
			if (i * delay_between_poll_us > 1000 &&
					!IS_FPGA_MAXIMUS_DC(ctx->dce_environment))
				DC_LOG_DC("REG_WAIT taking a while: %dms in %s line:%d\n",
						delay_between_poll_us * i / 1000,
						func_name, line);
			return;
		}
	}

	DC_LOG_WARNING("REG_WAIT timeout %dus * %d tries - %s line:%d\n",
			delay_between_poll_us, time_out_num_tries,
			func_name, line);

	if (!IS_FPGA_MAXIMUS_DC(ctx->dce_environment))
		BREAK_TO_DEBUGGER();
}