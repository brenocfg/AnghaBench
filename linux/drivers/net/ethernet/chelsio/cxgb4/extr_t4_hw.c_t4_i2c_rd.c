#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int pid; unsigned int did; unsigned int boffset; unsigned int blen; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ i2c; } ;
struct fw_ldst_cmd {TYPE_2__ u; void* cycles_to_len16; void* op_to_addrspace; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  ldst_cmd ;

/* Variables and functions */
 int EINVAL ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int /*<<< orphan*/  FW_LDST_ADDRSPC_I2C ; 
 int /*<<< orphan*/  FW_LDST_CMD ; 
 int FW_LDST_CMD_ADDRSPACE_V (int /*<<< orphan*/ ) ; 
 int FW_LEN16 (struct fw_ldst_cmd) ; 
 unsigned int I2C_PAGE_SIZE ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (struct fw_ldst_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_ldst_cmd*,int,struct fw_ldst_cmd*) ; 

int t4_i2c_rd(struct adapter *adap, unsigned int mbox, int port,
	      unsigned int devid, unsigned int offset,
	      unsigned int len, u8 *buf)
{
	struct fw_ldst_cmd ldst_cmd, ldst_rpl;
	unsigned int i2c_max = sizeof(ldst_cmd.u.i2c.data);
	int ret = 0;

	if (len > I2C_PAGE_SIZE)
		return -EINVAL;

	/* Dont allow reads that spans multiple pages */
	if (offset < I2C_PAGE_SIZE && offset + len > I2C_PAGE_SIZE)
		return -EINVAL;

	memset(&ldst_cmd, 0, sizeof(ldst_cmd));
	ldst_cmd.op_to_addrspace =
		cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
			    FW_CMD_REQUEST_F |
			    FW_CMD_READ_F |
			    FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_I2C));
	ldst_cmd.cycles_to_len16 = cpu_to_be32(FW_LEN16(ldst_cmd));
	ldst_cmd.u.i2c.pid = (port < 0 ? 0xff : port);
	ldst_cmd.u.i2c.did = devid;

	while (len > 0) {
		unsigned int i2c_len = (len < i2c_max) ? len : i2c_max;

		ldst_cmd.u.i2c.boffset = offset;
		ldst_cmd.u.i2c.blen = i2c_len;

		ret = t4_wr_mbox(adap, mbox, &ldst_cmd, sizeof(ldst_cmd),
				 &ldst_rpl);
		if (ret)
			break;

		memcpy(buf, ldst_rpl.u.i2c.data, i2c_len);
		offset += i2c_len;
		buf += i2c_len;
		len -= i2c_len;
	}

	return ret;
}