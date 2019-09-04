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
typedef  int /*<<< orphan*/  uint32_t ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_read_reg (struct dc_context const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_reg_field_value_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t generic_reg_get4(const struct dc_context *ctx, uint32_t addr,
		uint8_t shift1, uint32_t mask1, uint32_t *field_value1,
		uint8_t shift2, uint32_t mask2, uint32_t *field_value2,
		uint8_t shift3, uint32_t mask3, uint32_t *field_value3,
		uint8_t shift4, uint32_t mask4, uint32_t *field_value4)
{
	uint32_t reg_val = dm_read_reg(ctx, addr);
	*field_value1 = get_reg_field_value_ex(reg_val, mask1, shift1);
	*field_value2 = get_reg_field_value_ex(reg_val, mask2, shift2);
	*field_value3 = get_reg_field_value_ex(reg_val, mask3, shift3);
	*field_value4 = get_reg_field_value_ex(reg_val, mask4, shift4);
	return reg_val;
}