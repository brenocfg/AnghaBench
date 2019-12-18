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
typedef  scalar_t__ uint32_t ;
struct dc_context {TYPE_1__* perf_trace; int /*<<< orphan*/  cgs_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  read_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERR (char*) ; 
 scalar_t__ cgs_read_register (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_amdgpu_dc_rreg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

uint32_t dm_read_reg_func(
	const struct dc_context *ctx,
	uint32_t address,
	const char *func_name)
{
	uint32_t value;
#ifdef DM_CHECK_ADDR_0
	if (address == 0) {
		DC_ERR("invalid register read; address = 0\n");
		return 0;
	}
#endif
	value = cgs_read_register(ctx->cgs_device, address);
	trace_amdgpu_dc_rreg(&ctx->perf_trace->read_count, address, value);

	return value;
}