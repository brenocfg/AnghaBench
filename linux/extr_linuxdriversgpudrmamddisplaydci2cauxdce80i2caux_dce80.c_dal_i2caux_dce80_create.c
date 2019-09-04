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
struct i2caux_dce80 {struct i2caux base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  construct (struct i2caux_dce80*,struct dc_context*) ; 
 struct i2caux_dce80* kzalloc (int,int /*<<< orphan*/ ) ; 

struct i2caux *dal_i2caux_dce80_create(
	struct dc_context *ctx)
{
	struct i2caux_dce80 *i2caux_dce80 =
		kzalloc(sizeof(struct i2caux_dce80), GFP_KERNEL);

	if (!i2caux_dce80) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	construct(i2caux_dce80, ctx);
	return &i2caux_dce80->base;
}