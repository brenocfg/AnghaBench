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
 int EIO ; 

__attribute__((used)) static int drxdap_fasi_read_modify_write_reg16(struct i2c_device_addr *dev_addr,
						    u32 waddr,
						    u32 raddr,
						    u16 wdata, u16 *rdata)
{
	int rc = -EIO;

#if (DRXDAPFASI_LONG_ADDR_ALLOWED == 1)
	if (rdata == NULL)
		return -EINVAL;

	rc = drxdap_fasi_write_reg16(dev_addr, waddr, wdata, DRXDAP_FASI_RMW);
	if (rc == 0)
		rc = drxdap_fasi_read_reg16(dev_addr, raddr, rdata, 0);
#endif

	return rc;
}