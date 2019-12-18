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
struct zx_vga_i2c {int /*<<< orphan*/  lock; } ;
struct zx_vga {struct zx_vga_i2c* ddc; } ;
struct i2c_msg {int flags; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 struct zx_vga* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int zx_vga_i2c_read (struct zx_vga*,struct i2c_msg*) ; 
 int zx_vga_i2c_write (struct zx_vga*,struct i2c_msg*) ; 

__attribute__((used)) static int zx_vga_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			   int num)
{
	struct zx_vga *vga = i2c_get_adapdata(adap);
	struct zx_vga_i2c *ddc = vga->ddc;
	int ret = 0;
	int i;

	mutex_lock(&ddc->lock);

	for (i = 0; i < num; i++) {
		if (msgs[i].flags & I2C_M_RD)
			ret = zx_vga_i2c_read(vga, &msgs[i]);
		else
			ret = zx_vga_i2c_write(vga, &msgs[i]);

		if (ret < 0)
			break;
	}

	if (!ret)
		ret = num;

	mutex_unlock(&ddc->lock);

	return ret;
}