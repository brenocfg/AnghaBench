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
typedef  int u8 ;
typedef  int u32 ;
struct pca954x {int last_chan; struct chip_desc* chip; struct i2c_client* client; } ;
struct i2c_mux_core {int /*<<< orphan*/  parent; } ;
struct i2c_client {int dummy; } ;
struct chip_desc {scalar_t__ muxtype; int enable; } ;

/* Variables and functions */
 struct pca954x* i2c_mux_priv (struct i2c_mux_core*) ; 
 scalar_t__ pca954x_ismux ; 
 int pca954x_reg_write (int /*<<< orphan*/ ,struct i2c_client*,int) ; 

__attribute__((used)) static int pca954x_select_chan(struct i2c_mux_core *muxc, u32 chan)
{
	struct pca954x *data = i2c_mux_priv(muxc);
	struct i2c_client *client = data->client;
	const struct chip_desc *chip = data->chip;
	u8 regval;
	int ret = 0;

	/* we make switches look like muxes, not sure how to be smarter */
	if (chip->muxtype == pca954x_ismux)
		regval = chan | chip->enable;
	else
		regval = 1 << chan;

	/* Only select the channel if its different from the last channel */
	if (data->last_chan != regval) {
		ret = pca954x_reg_write(muxc->parent, client, regval);
		data->last_chan = ret < 0 ? 0 : regval;
	}

	return ret;
}