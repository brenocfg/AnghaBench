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
typedef  int u16 ;
struct i2c_device_addr {int /*<<< orphan*/  i2c_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRXDAPFASI_LONG_ADDR_ALLOWED ; 
 int DRXDAP_FASI_FLAGS ; 
 scalar_t__ DRXDAP_FASI_LONG_FORMAT (int) ; 
 int DRXDAP_FASI_MODEFLAGS ; 
 scalar_t__ DRXDAP_FASI_OFFSET_TOO_LARGE (int) ; 
 int DRXDAP_FASI_RMW ; 
 int DRXDAP_FASI_SINGLE_MASTER ; 
 int DRXDAP_MAX_RCHUNKSIZE ; 
 int DRXDAP_MAX_WCHUNKSIZE ; 
 int EINVAL ; 
 scalar_t__ IS_I2C_10BIT (int /*<<< orphan*/ ) ; 
 int drxbsp_i2c_write_read (struct i2c_device_addr*,int,scalar_t__*,struct i2c_device_addr*,int,scalar_t__*) ; 

__attribute__((used)) static int drxdap_fasi_read_block(struct i2c_device_addr *dev_addr,
					 u32 addr,
					 u16 datasize,
					 u8 *data, u32 flags)
{
	u8 buf[4];
	u16 bufx;
	int rc;
	u16 overhead_size = 0;

	/* Check parameters ******************************************************* */
	if (dev_addr == NULL)
		return -EINVAL;

	overhead_size = (IS_I2C_10BIT(dev_addr->i2c_addr) ? 2 : 1) +
	    (DRXDAP_FASI_LONG_FORMAT(addr) ? 4 : 2);

	if ((DRXDAP_FASI_OFFSET_TOO_LARGE(addr)) ||
	    ((!(DRXDAPFASI_LONG_ADDR_ALLOWED)) &&
	     DRXDAP_FASI_LONG_FORMAT(addr)) ||
	    (overhead_size > (DRXDAP_MAX_WCHUNKSIZE)) ||
	    ((datasize != 0) && (data == NULL)) || ((datasize & 1) == 1)) {
		return -EINVAL;
	}

	/* ReadModifyWrite & mode flag bits are not allowed */
	flags &= (~DRXDAP_FASI_RMW & ~DRXDAP_FASI_MODEFLAGS);
#if DRXDAP_SINGLE_MASTER
	flags |= DRXDAP_FASI_SINGLE_MASTER;
#endif

	/* Read block from I2C **************************************************** */
	do {
		u16 todo = (datasize < DRXDAP_MAX_RCHUNKSIZE ?
			      datasize : DRXDAP_MAX_RCHUNKSIZE);

		bufx = 0;

		addr &= ~DRXDAP_FASI_FLAGS;
		addr |= flags;

#if ((DRXDAPFASI_LONG_ADDR_ALLOWED == 1) && (DRXDAPFASI_SHORT_ADDR_ALLOWED == 1))
		/* short format address preferred but long format otherwise */
		if (DRXDAP_FASI_LONG_FORMAT(addr)) {
#endif
#if (DRXDAPFASI_LONG_ADDR_ALLOWED == 1)
			buf[bufx++] = (u8) (((addr << 1) & 0xFF) | 0x01);
			buf[bufx++] = (u8) ((addr >> 16) & 0xFF);
			buf[bufx++] = (u8) ((addr >> 24) & 0xFF);
			buf[bufx++] = (u8) ((addr >> 7) & 0xFF);
#endif
#if ((DRXDAPFASI_LONG_ADDR_ALLOWED == 1) && (DRXDAPFASI_SHORT_ADDR_ALLOWED == 1))
		} else {
#endif
#if (DRXDAPFASI_SHORT_ADDR_ALLOWED == 1)
			buf[bufx++] = (u8) ((addr << 1) & 0xFF);
			buf[bufx++] =
			    (u8) (((addr >> 16) & 0x0F) |
				    ((addr >> 18) & 0xF0));
#endif
#if ((DRXDAPFASI_LONG_ADDR_ALLOWED == 1) && (DRXDAPFASI_SHORT_ADDR_ALLOWED == 1))
		}
#endif

#if DRXDAP_SINGLE_MASTER
		/*
		 * In single master mode, split the read and write actions.
		 * No special action is needed for write chunks here.
		 */
		rc = drxbsp_i2c_write_read(dev_addr, bufx, buf,
					   NULL, 0, NULL);
		if (rc == 0)
			rc = drxbsp_i2c_write_read(NULL, 0, NULL, dev_addr, todo, data);
#else
		/* In multi master mode, do everything in one RW action */
		rc = drxbsp_i2c_write_read(dev_addr, bufx, buf, dev_addr, todo,
					  data);
#endif
		data += todo;
		addr += (todo >> 1);
		datasize -= todo;
	} while (datasize && rc == 0);

	return rc;
}