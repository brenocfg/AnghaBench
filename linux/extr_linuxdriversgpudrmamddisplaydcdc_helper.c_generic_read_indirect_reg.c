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
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_read_reg (struct dc_context const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t generic_read_indirect_reg(const struct dc_context *ctx,
		uint32_t addr_index, uint32_t addr_data,
		uint32_t index)
{
	uint32_t value = 0;

	dm_write_reg(ctx, addr_index, index);
	value = dm_read_reg(ctx, addr_data);

	return value;
}