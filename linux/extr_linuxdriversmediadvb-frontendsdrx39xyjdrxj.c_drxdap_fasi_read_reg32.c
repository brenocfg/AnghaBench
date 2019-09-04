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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct i2c_device_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int drxdap_fasi_read_block (struct i2c_device_addr*,int,int,scalar_t__*,int) ; 

__attribute__((used)) static int drxdap_fasi_read_reg32(struct i2c_device_addr *dev_addr,
					 u32 addr,
					 u32 *data, u32 flags)
{
	u8 buf[sizeof(*data)];
	int rc;

	if (!data)
		return -EINVAL;

	rc = drxdap_fasi_read_block(dev_addr, addr, sizeof(*data), buf, flags);
	*data = (((u32) buf[0]) << 0) +
	    (((u32) buf[1]) << 8) +
	    (((u32) buf[2]) << 16) + (((u32) buf[3]) << 24);
	return rc;
}