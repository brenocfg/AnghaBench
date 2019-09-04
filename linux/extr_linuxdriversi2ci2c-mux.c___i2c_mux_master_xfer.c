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
struct i2c_mux_priv {int /*<<< orphan*/  chan_id; struct i2c_mux_core* muxc; } ;
struct i2c_mux_core {int (* select ) (struct i2c_mux_core*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* deselect ) (struct i2c_mux_core*,int /*<<< orphan*/ ) ;struct i2c_adapter* parent; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {struct i2c_mux_priv* algo_data; } ;

/* Variables and functions */
 int __i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int stub1 (struct i2c_mux_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct i2c_mux_core*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __i2c_mux_master_xfer(struct i2c_adapter *adap,
				 struct i2c_msg msgs[], int num)
{
	struct i2c_mux_priv *priv = adap->algo_data;
	struct i2c_mux_core *muxc = priv->muxc;
	struct i2c_adapter *parent = muxc->parent;
	int ret;

	/* Switch to the right mux port and perform the transfer. */

	ret = muxc->select(muxc, priv->chan_id);
	if (ret >= 0)
		ret = __i2c_transfer(parent, msgs, num);
	if (muxc->deselect)
		muxc->deselect(muxc, priv->chan_id);

	return ret;
}