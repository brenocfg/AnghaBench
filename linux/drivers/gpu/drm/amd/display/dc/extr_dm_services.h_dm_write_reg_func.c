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
struct TYPE_2__ {int /*<<< orphan*/  write_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERR (char*) ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_amdgpu_dc_wreg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void dm_write_reg_func(
	const struct dc_context *ctx,
	uint32_t address,
	uint32_t value,
	const char *func_name)
{
#ifdef DM_CHECK_ADDR_0
	if (address == 0) {
		DC_ERR("invalid register write. address = 0");
		return;
	}
#endif
	cgs_write_register(ctx->cgs_device, address, value);
	trace_amdgpu_dc_wreg(&ctx->perf_trace->write_count, address, value);
}