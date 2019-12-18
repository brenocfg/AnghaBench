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
 int /*<<< orphan*/  GAMMA_CORR_CONTROL ; 
 int /*<<< orphan*/  GAMMA_CORR_MODE ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmGAMMA_CORR_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void configure_regamma_mode(struct dce_transform *xfm_dce, uint32_t mode)
{
	uint32_t value = 0;

	set_reg_field_value(
				value,
				mode,
				GAMMA_CORR_CONTROL,
				GAMMA_CORR_MODE);

	dm_write_reg(xfm_dce->base.ctx, mmGAMMA_CORR_CONTROL, 0);
}