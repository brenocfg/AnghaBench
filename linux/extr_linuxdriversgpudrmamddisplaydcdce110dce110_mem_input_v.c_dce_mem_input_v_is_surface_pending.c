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
struct mem_input {int /*<<< orphan*/  request_address; int /*<<< orphan*/  current_address; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct dce_mem_input {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_SURFACE_UPDATE_PENDING ; 
 struct dce_mem_input* TO_DCE_MEM_INPUT (struct mem_input*) ; 
 int /*<<< orphan*/  UNP_GRPH_UPDATE ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUNP_GRPH_UPDATE ; 

bool dce_mem_input_v_is_surface_pending(struct mem_input *mem_input)
{
	struct dce_mem_input *mem_input110 = TO_DCE_MEM_INPUT(mem_input);
	uint32_t value;

	value = dm_read_reg(mem_input110->base.ctx, mmUNP_GRPH_UPDATE);

	if (get_reg_field_value(value, UNP_GRPH_UPDATE,
			GRPH_SURFACE_UPDATE_PENDING))
		return true;

	mem_input->current_address = mem_input->request_address;
	return false;
}