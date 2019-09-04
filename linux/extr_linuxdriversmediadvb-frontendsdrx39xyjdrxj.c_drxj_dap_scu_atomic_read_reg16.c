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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct i2c_device_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int drxj_dap_scu_atomic_read_write_block (struct i2c_device_addr*,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static
int drxj_dap_scu_atomic_read_reg16(struct i2c_device_addr *dev_addr,
					 u32 addr,
					 u16 *data, u32 flags)
{
	u8 buf[2] = { 0 };
	int rc = -EIO;
	u16 word = 0;

	if (!data)
		return -EINVAL;

	rc = drxj_dap_scu_atomic_read_write_block(dev_addr, addr, 2, buf, true);
	if (rc < 0)
		return rc;

	word = (u16) (buf[0] + (buf[1] << 8));

	*data = word;

	return rc;
}