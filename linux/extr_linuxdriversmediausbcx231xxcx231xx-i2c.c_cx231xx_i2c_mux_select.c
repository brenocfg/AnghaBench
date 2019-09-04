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
struct i2c_mux_core {int dummy; } ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int cx231xx_enable_i2c_port_3 (struct cx231xx*,int /*<<< orphan*/ ) ; 
 struct cx231xx* i2c_mux_priv (struct i2c_mux_core*) ; 

__attribute__((used)) static int cx231xx_i2c_mux_select(struct i2c_mux_core *muxc, u32 chan_id)
{
	struct cx231xx *dev = i2c_mux_priv(muxc);

	return cx231xx_enable_i2c_port_3(dev, chan_id);
}