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
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  construct (struct i2caux*,struct dc_context*) ; 
 struct i2caux* kzalloc (int,int /*<<< orphan*/ ) ; 

struct i2caux *dal_i2caux_diag_fpga_create(
	struct dc_context *ctx)
{
	struct i2caux *i2caux =	kzalloc(sizeof(struct i2caux),
					       GFP_KERNEL);

	if (!i2caux) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	construct(i2caux, ctx);
	return i2caux;
}