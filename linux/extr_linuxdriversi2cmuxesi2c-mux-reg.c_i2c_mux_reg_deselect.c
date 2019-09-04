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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  idle; scalar_t__ idle_in_use; } ;
struct regmux {TYPE_1__ data; } ;
struct i2c_mux_core {int dummy; } ;

/* Variables and functions */
 struct regmux* i2c_mux_priv (struct i2c_mux_core*) ; 
 int i2c_mux_reg_set (struct regmux*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_mux_reg_deselect(struct i2c_mux_core *muxc, u32 chan)
{
	struct regmux *mux = i2c_mux_priv(muxc);

	if (mux->data.idle_in_use)
		return i2c_mux_reg_set(mux, mux->data.idle);

	return 0;
}