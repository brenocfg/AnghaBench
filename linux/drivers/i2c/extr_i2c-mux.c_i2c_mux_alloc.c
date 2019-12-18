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
typedef  int u32 ;
struct i2c_mux_core {int mux_locked; int arbitrator; int gate; int (* select ) (struct i2c_mux_core*,int) ;int (* deselect ) (struct i2c_mux_core*,int) ;int max_adapters; struct device* dev; struct i2c_adapter* parent; int /*<<< orphan*/ * adapter; int /*<<< orphan*/ * priv; } ;
struct i2c_adapter {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_MUX_ARBITRATOR ; 
 int I2C_MUX_GATE ; 
 int I2C_MUX_LOCKED ; 
 int /*<<< orphan*/  adapter ; 
 struct i2c_mux_core* devm_kzalloc (struct device*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ struct_size (struct i2c_mux_core*,int /*<<< orphan*/ ,int) ; 

struct i2c_mux_core *i2c_mux_alloc(struct i2c_adapter *parent,
				   struct device *dev, int max_adapters,
				   int sizeof_priv, u32 flags,
				   int (*select)(struct i2c_mux_core *, u32),
				   int (*deselect)(struct i2c_mux_core *, u32))
{
	struct i2c_mux_core *muxc;

	muxc = devm_kzalloc(dev, struct_size(muxc, adapter, max_adapters)
			    + sizeof_priv, GFP_KERNEL);
	if (!muxc)
		return NULL;
	if (sizeof_priv)
		muxc->priv = &muxc->adapter[max_adapters];

	muxc->parent = parent;
	muxc->dev = dev;
	if (flags & I2C_MUX_LOCKED)
		muxc->mux_locked = true;
	if (flags & I2C_MUX_ARBITRATOR)
		muxc->arbitrator = true;
	if (flags & I2C_MUX_GATE)
		muxc->gate = true;
	muxc->select = select;
	muxc->deselect = deselect;
	muxc->max_adapters = max_adapters;

	return muxc;
}