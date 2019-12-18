#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i2c_demux_pinctrl_priv {size_t cur_chan; TYPE_1__* chan; } ;
struct i2c_adapter {TYPE_2__* algo; struct i2c_demux_pinctrl_priv* algo_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* functionality ) (struct i2c_adapter*) ;} ;
struct TYPE_3__ {struct i2c_adapter* parent_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct i2c_adapter*) ; 

__attribute__((used)) static u32 i2c_demux_functionality(struct i2c_adapter *adap)
{
	struct i2c_demux_pinctrl_priv *priv = adap->algo_data;
	struct i2c_adapter *parent = priv->chan[priv->cur_chan].parent_adap;

	return parent->algo->functionality(parent);
}