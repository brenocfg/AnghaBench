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
typedef  scalar_t__ u32 ;
struct i2c_demux_pinctrl_priv {scalar_t__ cur_chan; } ;

/* Variables and functions */
 int i2c_demux_activate_master (struct i2c_demux_pinctrl_priv*,scalar_t__) ; 
 int i2c_demux_deactivate_master (struct i2c_demux_pinctrl_priv*) ; 

__attribute__((used)) static int i2c_demux_change_master(struct i2c_demux_pinctrl_priv *priv, u32 new_chan)
{
	int ret;

	if (new_chan == priv->cur_chan)
		return 0;

	ret = i2c_demux_deactivate_master(priv);
	if (ret)
		return ret;

	return i2c_demux_activate_master(priv, new_chan);
}