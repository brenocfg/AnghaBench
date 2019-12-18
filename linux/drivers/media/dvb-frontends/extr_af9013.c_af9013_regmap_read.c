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
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct af9013_state {scalar_t__ ts_mode; } ;

/* Variables and functions */
 scalar_t__ AF9013_TS_MODE_USB ; 
 int af9013_rregs (struct i2c_client*,int,int,int*,unsigned int const,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct af9013_state* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int af9013_regmap_read(void *context, const void *reg_buf,
			      size_t reg_size, void *val_buf, size_t val_size)
{
	struct i2c_client *client = context;
	struct af9013_state *state = i2c_get_clientdata(client);
	int ret, i;
	u8 cmd;
	u8 lock = !((u8 *)reg_buf)[0];
	u16 reg = ((u8 *)reg_buf)[1] << 8 | ((u8 *)reg_buf)[2] << 0;
	u8 *val = &((u8 *)val_buf)[0];
	const unsigned int len = val_size;

	if (state->ts_mode == AF9013_TS_MODE_USB && (reg & 0xff00) != 0xae00) {
		cmd = 0 << 7|0 << 6|(len - 1) << 2|1 << 1|0 << 0;
		ret = af9013_rregs(client, cmd, reg, val_buf, len, lock);
		if (ret)
			goto err;
	} else {
		cmd = 0 << 7|0 << 6|(1 - 1) << 2|1 << 1|0 << 0;
		for (i = 0; i < len; i++) {
			ret = af9013_rregs(client, cmd, reg + i, val + i, 1,
					   lock);
			if (ret)
				goto err;
		}
	}

	return 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	return ret;
}