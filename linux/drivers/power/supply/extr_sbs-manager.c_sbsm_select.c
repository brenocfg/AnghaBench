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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sbsm_data {scalar_t__ cur_chan; TYPE_1__* client; } ;
struct i2c_mux_core {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int /*<<< orphan*/  SBSM_CMD_BATSYSSTATE ; 
 scalar_t__ SBSM_SMB_BAT_OFFSET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 struct sbsm_data* i2c_mux_priv (struct i2c_mux_core*) ; 
 int sbsm_write_word (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbsm_select(struct i2c_mux_core *muxc, u32 chan)
{
	struct sbsm_data *data = i2c_mux_priv(muxc);
	struct device *dev = &data->client->dev;
	int ret = 0;
	u16 reg;

	if (data->cur_chan == chan)
		return ret;

	/* chan goes from 1 ... 4 */
	reg = BIT(SBSM_SMB_BAT_OFFSET + chan);
	ret = sbsm_write_word(data->client, SBSM_CMD_BATSYSSTATE, reg);
	if (ret)
		dev_err(dev, "Failed to select channel %i\n", chan);
	else
		data->cur_chan = chan;

	return ret;
}