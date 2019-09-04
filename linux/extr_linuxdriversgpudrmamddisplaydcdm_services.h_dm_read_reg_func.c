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
typedef  int /*<<< orphan*/  uint32_t ;
struct dc_context {int /*<<< orphan*/  cgs_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t dm_read_reg_func(
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

	return value;
}