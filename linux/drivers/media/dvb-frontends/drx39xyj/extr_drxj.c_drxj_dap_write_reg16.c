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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_device_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int drxdap_fasi_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drxj_dap_write_aud_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_handled_by_aud_tr_if (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drxj_dap_write_reg16(struct i2c_device_addr *dev_addr,
				       u32 addr,
				       u16 data, u32 flags)
{
	int stat = -EIO;

	/* Check param */
	if (dev_addr == NULL)
		return -EINVAL;

	if (is_handled_by_aud_tr_if(addr))
		stat = drxj_dap_write_aud_reg16(dev_addr, addr, data);
	else
		stat = drxdap_fasi_write_reg16(dev_addr,
							    addr, data, flags);

	return stat;
}