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
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int drxdap_fasi_write_block (struct i2c_device_addr*,int,int,scalar_t__*,int) ; 

__attribute__((used)) static int drxdap_fasi_write_reg32(struct i2c_device_addr *dev_addr,
					  u32 addr,
					  u32 data, u32 flags)
{
	u8 buf[sizeof(data)];

	buf[0] = (u8) ((data >> 0) & 0xFF);
	buf[1] = (u8) ((data >> 8) & 0xFF);
	buf[2] = (u8) ((data >> 16) & 0xFF);
	buf[3] = (u8) ((data >> 24) & 0xFF);

	return drxdap_fasi_write_block(dev_addr, addr, sizeof(data), buf, flags);
}