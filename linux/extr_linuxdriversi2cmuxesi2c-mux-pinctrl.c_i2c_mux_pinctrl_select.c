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
typedef  size_t u32 ;
struct i2c_mux_pinctrl {int /*<<< orphan*/ * states; int /*<<< orphan*/  pinctrl; } ;
struct i2c_mux_core {int dummy; } ;

/* Variables and functions */
 struct i2c_mux_pinctrl* i2c_mux_priv (struct i2c_mux_core*) ; 
 int pinctrl_select_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_mux_pinctrl_select(struct i2c_mux_core *muxc, u32 chan)
{
	struct i2c_mux_pinctrl *mux = i2c_mux_priv(muxc);

	return pinctrl_select_state(mux->pinctrl, mux->states[chan]);
}