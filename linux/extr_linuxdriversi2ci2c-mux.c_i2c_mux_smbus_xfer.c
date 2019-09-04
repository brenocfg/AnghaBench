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
typedef  union i2c_smbus_data {int dummy; } i2c_smbus_data ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_mux_priv {int /*<<< orphan*/  chan_id; struct i2c_mux_core* muxc; } ;
struct i2c_mux_core {int (* select ) (struct i2c_mux_core*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* deselect ) (struct i2c_mux_core*,int /*<<< orphan*/ ) ;struct i2c_adapter* parent; } ;
struct i2c_adapter {struct i2c_mux_priv* algo_data; } ;

/* Variables and functions */
 int i2c_smbus_xfer (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*) ; 
 int stub1 (struct i2c_mux_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct i2c_mux_core*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_mux_smbus_xfer(struct i2c_adapter *adap,
			      u16 addr, unsigned short flags,
			      char read_write, u8 command,
			      int size, union i2c_smbus_data *data)
{
	struct i2c_mux_priv *priv = adap->algo_data;
	struct i2c_mux_core *muxc = priv->muxc;
	struct i2c_adapter *parent = muxc->parent;
	int ret;

	/* Select the right mux port and perform the transfer. */

	ret = muxc->select(muxc, priv->chan_id);
	if (ret >= 0)
		ret = i2c_smbus_xfer(parent, addr, flags,
				     read_write, command, size, data);
	if (muxc->deselect)
		muxc->deselect(muxc, priv->chan_id);

	return ret;
}