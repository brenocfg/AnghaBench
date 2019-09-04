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
struct dce_transform {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCLV_UPDATE ; 
 int /*<<< orphan*/  SCL_COEF_UPDATE_COMPLETE ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSCLV_UPDATE ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_coeff_update_complete(
		struct dce_transform *xfm_dce)
{
	uint32_t value;

	value = dm_read_reg(xfm_dce->base.ctx, mmSCLV_UPDATE);
	set_reg_field_value(value, 1, SCLV_UPDATE, SCL_COEF_UPDATE_COMPLETE);
	dm_write_reg(xfm_dce->base.ctx, mmSCLV_UPDATE, value);
}