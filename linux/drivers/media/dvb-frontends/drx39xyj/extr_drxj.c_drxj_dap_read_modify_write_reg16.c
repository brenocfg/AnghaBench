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
 int drxdap_fasi_read_modify_write_reg16 (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drxj_dap_rm_write_reg16short (struct i2c_device_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drxj_dap_read_modify_write_reg16(struct i2c_device_addr *dev_addr,
						 u32 waddr,
						 u32 raddr,
						 u16 wdata, u16 *rdata)
{
	/* TODO: correct short/long addressing format decision,
	   now long format has higher prio then short because short also
	   needs virt bnks (not impl yet) for certain audio registers */
#if (DRXDAPFASI_LONG_ADDR_ALLOWED == 1)
	return drxdap_fasi_read_modify_write_reg16(dev_addr,
							  waddr,
							  raddr, wdata, rdata);
#else
	return drxj_dap_rm_write_reg16short(dev_addr, waddr, raddr, wdata, rdata);
#endif
}