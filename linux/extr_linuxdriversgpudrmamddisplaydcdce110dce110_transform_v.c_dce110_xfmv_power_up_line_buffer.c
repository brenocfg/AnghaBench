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
struct transform {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct dce_transform {TYPE_1__ base; int /*<<< orphan*/  lb_memory_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBV_MEMORY_CTRL ; 
 int /*<<< orphan*/  LB_MEMORY_CONFIG ; 
 int /*<<< orphan*/  LB_MEMORY_SIZE ; 
 struct dce_transform* TO_DCE_TRANSFORM (struct transform*) ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmLBV_MEMORY_CTRL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dce110_xfmv_power_up_line_buffer(struct transform *xfm)
{
	struct dce_transform *xfm_dce = TO_DCE_TRANSFORM(xfm);
	uint32_t value;

	value = dm_read_reg(xfm_dce->base.ctx, mmLBV_MEMORY_CTRL);

	/*Use all three pieces of memory always*/
	set_reg_field_value(value, 0, LBV_MEMORY_CTRL, LB_MEMORY_CONFIG);
	/*hard coded number DCE11 1712(0x6B0) Partitions: 720/960/1712*/
	set_reg_field_value(value, xfm_dce->lb_memory_size, LBV_MEMORY_CTRL,
			LB_MEMORY_SIZE);

	dm_write_reg(xfm_dce->base.ctx, mmLBV_MEMORY_CTRL, value);

	return true;
}