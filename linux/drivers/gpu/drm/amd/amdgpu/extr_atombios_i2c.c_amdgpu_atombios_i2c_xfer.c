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
struct i2c_msg {int len; int flags; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct amdgpu_i2c_chan {int dummy; } ;

/* Variables and functions */
 int ATOM_MAX_HW_I2C_READ ; 
 int ATOM_MAX_HW_I2C_WRITE ; 
 int /*<<< orphan*/  HW_I2C_READ ; 
 int /*<<< orphan*/  HW_I2C_WRITE ; 
 int I2C_M_RD ; 
 int amdgpu_atombios_i2c_process_i2c_ch (struct amdgpu_i2c_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct amdgpu_i2c_chan* i2c_get_adapdata (struct i2c_adapter*) ; 

int amdgpu_atombios_i2c_xfer(struct i2c_adapter *i2c_adap,
		      struct i2c_msg *msgs, int num)
{
	struct amdgpu_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	struct i2c_msg *p;
	int i, remaining, current_count, buffer_offset, max_bytes, ret;
	u8 flags;

	/* check for bus probe */
	p = &msgs[0];
	if ((num == 1) && (p->len == 0)) {
		ret = amdgpu_atombios_i2c_process_i2c_ch(i2c,
						  p->addr, HW_I2C_WRITE,
						  NULL, 0);
		if (ret)
			return ret;
		else
			return num;
	}

	for (i = 0; i < num; i++) {
		p = &msgs[i];
		remaining = p->len;
		buffer_offset = 0;
		/* max_bytes are a limitation of ProcessI2cChannelTransaction not the hw */
		if (p->flags & I2C_M_RD) {
			max_bytes = ATOM_MAX_HW_I2C_READ;
			flags = HW_I2C_READ;
		} else {
			max_bytes = ATOM_MAX_HW_I2C_WRITE;
			flags = HW_I2C_WRITE;
		}
		while (remaining) {
			if (remaining > max_bytes)
				current_count = max_bytes;
			else
				current_count = remaining;
			ret = amdgpu_atombios_i2c_process_i2c_ch(i2c,
							  p->addr, flags,
							  &p->buf[buffer_offset], current_count);
			if (ret)
				return ret;
			remaining -= current_count;
			buffer_offset += current_count;
		}
	}

	return num;
}