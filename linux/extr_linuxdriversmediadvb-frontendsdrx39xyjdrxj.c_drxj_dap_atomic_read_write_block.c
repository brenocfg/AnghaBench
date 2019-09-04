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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct i2c_device_addr {int dummy; } ;
struct drxj_hi_cmd {int param1; int param2; int param3; int param4; int param5; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 scalar_t__ DRXDAP_FASI_ADDR2BANK (scalar_t__) ; 
 int DRXDAP_FASI_ADDR2BLOCK (scalar_t__) ; 
 scalar_t__ DRXDAP_FASI_ADDR2OFFSET (scalar_t__) ; 
 scalar_t__ DRXJ_HI_ATOMIC_BUF_START ; 
 int DRXJ_HI_ATOMIC_READ ; 
 int DRXJ_HI_ATOMIC_WRITE ; 
 int EINVAL ; 
 int /*<<< orphan*/  SIO_HI_RA_RAM_CMD_ATOMIC_COPY ; 
 int drxj_dap_read_reg16 (struct i2c_device_addr*,scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drxj_dap_write_reg16 (struct i2c_device_addr*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int hi_command (struct i2c_device_addr*,struct drxj_hi_cmd*,int*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static
int drxj_dap_atomic_read_write_block(struct i2c_device_addr *dev_addr,
					  u32 addr,
					  u16 datasize,
					  u8 *data, bool read_flag)
{
	struct drxj_hi_cmd hi_cmd;
	int rc;
	u16 word;
	u16 dummy = 0;
	u16 i = 0;

	/* Parameter check */
	if (!data || !dev_addr || ((datasize % 2)) || ((datasize / 2) > 8))
		return -EINVAL;

	/* Set up HI parameters to read or write n bytes */
	hi_cmd.cmd = SIO_HI_RA_RAM_CMD_ATOMIC_COPY;
	hi_cmd.param1 =
	    (u16) ((DRXDAP_FASI_ADDR2BLOCK(DRXJ_HI_ATOMIC_BUF_START) << 6) +
		     DRXDAP_FASI_ADDR2BANK(DRXJ_HI_ATOMIC_BUF_START));
	hi_cmd.param2 =
	    (u16) DRXDAP_FASI_ADDR2OFFSET(DRXJ_HI_ATOMIC_BUF_START);
	hi_cmd.param3 = (u16) ((datasize / 2) - 1);
	if (!read_flag)
		hi_cmd.param3 |= DRXJ_HI_ATOMIC_WRITE;
	else
		hi_cmd.param3 |= DRXJ_HI_ATOMIC_READ;
	hi_cmd.param4 = (u16) ((DRXDAP_FASI_ADDR2BLOCK(addr) << 6) +
				DRXDAP_FASI_ADDR2BANK(addr));
	hi_cmd.param5 = (u16) DRXDAP_FASI_ADDR2OFFSET(addr);

	if (!read_flag) {
		/* write data to buffer */
		for (i = 0; i < (datasize / 2); i++) {

			word = ((u16) data[2 * i]);
			word += (((u16) data[(2 * i) + 1]) << 8);
			drxj_dap_write_reg16(dev_addr,
					     (DRXJ_HI_ATOMIC_BUF_START + i),
					    word, 0);
		}
	}

	rc = hi_command(dev_addr, &hi_cmd, &dummy);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	if (read_flag) {
		/* read data from buffer */
		for (i = 0; i < (datasize / 2); i++) {
			rc = drxj_dap_read_reg16(dev_addr,
						 (DRXJ_HI_ATOMIC_BUF_START + i),
						 &word, 0);
			if (rc) {
				pr_err("error %d\n", rc);
				goto rw_error;
			}
			data[2 * i] = (u8) (word & 0xFF);
			data[(2 * i) + 1] = (u8) (word >> 8);
		}
	}

	return 0;

rw_error:
	return rc;

}