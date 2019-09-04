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
struct i2caux {int /*<<< orphan*/ * funcs; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_i2caux_construct (struct i2caux*,struct dc_context*) ; 
 int /*<<< orphan*/  i2caux_funcs ; 

__attribute__((used)) static void construct(
	struct i2caux *i2caux,
	struct dc_context *ctx)
{
	dal_i2caux_construct(i2caux, ctx);
	i2caux->funcs = &i2caux_funcs;
}