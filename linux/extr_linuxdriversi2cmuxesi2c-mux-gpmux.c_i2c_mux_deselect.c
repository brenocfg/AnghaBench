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
typedef  int /*<<< orphan*/  u32 ;
struct mux {int /*<<< orphan*/  control; scalar_t__ do_not_deselect; } ;
struct i2c_mux_core {int dummy; } ;

/* Variables and functions */
 struct mux* i2c_mux_priv (struct i2c_mux_core*) ; 
 int mux_control_deselect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_mux_deselect(struct i2c_mux_core *muxc, u32 chan)
{
	struct mux *mux = i2c_mux_priv(muxc);

	if (mux->do_not_deselect)
		return 0;

	return mux_control_deselect(mux->control);
}