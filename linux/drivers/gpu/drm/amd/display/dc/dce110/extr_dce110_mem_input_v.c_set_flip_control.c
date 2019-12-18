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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct dce_mem_input {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_SURFACE_UPDATE_PENDING_MODE ; 
 int /*<<< orphan*/  UNP_FLIP_CONTROL ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUNP_FLIP_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_flip_control(
	struct dce_mem_input *mem_input110,
	bool immediate)
{
	uint32_t value = 0;

	value = dm_read_reg(
			mem_input110->base.ctx,
			mmUNP_FLIP_CONTROL);

	set_reg_field_value(value, 1,
			UNP_FLIP_CONTROL,
			GRPH_SURFACE_UPDATE_PENDING_MODE);

	dm_write_reg(
			mem_input110->base.ctx,
			mmUNP_FLIP_CONTROL,
			value);
}