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
typedef  int /*<<< orphan*/  u8 ;
struct mma8450 {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMA8450_OUT_X_LSB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,unsigned int,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma8450_read_block(struct mma8450 *m, unsigned off,
			      u8 *buf, size_t size)
{
	struct i2c_client *c = m->client;
	int err;

	err = i2c_smbus_read_i2c_block_data(c, off, size, buf);
	if (err < 0) {
		dev_err(&c->dev,
			"failed to read block data at 0x%02x, error %d\n",
			MMA8450_OUT_X_LSB, err);
		return err;
	}

	return 0;
}