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
typedef  int u16 ;
struct i2c_device_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int drxdap_fasi_read_block (struct i2c_device_addr*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drxdap_fasi_read_reg16(struct i2c_device_addr *dev_addr,
					 u32 addr,
					 u16 *data, u32 flags)
{
	u8 buf[sizeof(*data)];
	int rc;

	if (!data)
		return -EINVAL;

	rc = drxdap_fasi_read_block(dev_addr, addr, sizeof(*data), buf, flags);
	*data = buf[0] + (((u16) buf[1]) << 8);
	return rc;
}