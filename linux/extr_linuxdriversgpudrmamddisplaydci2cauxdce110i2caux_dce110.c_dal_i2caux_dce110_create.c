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
struct i2caux {int dummy; } ;
struct i2caux_dce110 {struct i2caux base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dal_i2caux_dce110_construct (struct i2caux_dce110*,struct dc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dce110_aux_regs ; 
 int /*<<< orphan*/  i2c_hw_engine_regs ; 
 int /*<<< orphan*/  i2c_mask ; 
 int /*<<< orphan*/  i2c_shift ; 
 struct i2caux_dce110* kzalloc (int,int /*<<< orphan*/ ) ; 

struct i2caux *dal_i2caux_dce110_create(
	struct dc_context *ctx)
{
	struct i2caux_dce110 *i2caux_dce110 =
		kzalloc(sizeof(struct i2caux_dce110), GFP_KERNEL);

	if (!i2caux_dce110) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	dal_i2caux_dce110_construct(i2caux_dce110,
				    ctx,
				    ARRAY_SIZE(dce110_aux_regs),
				    dce110_aux_regs,
				    i2c_hw_engine_regs,
				    &i2c_shift,
				    &i2c_mask);
	return &i2caux_dce110->base;
}