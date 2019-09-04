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
typedef  int u32 ;
struct TYPE_3__ {void* val; void* addr; } ;
struct TYPE_4__ {TYPE_1__ addrval; } ;
struct fw_ldst_cmd {TYPE_2__ u; void* cycles_to_len16; void* op_to_addrspace; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int /*<<< orphan*/  FW_LDST_ADDRSPC_FIRMWARE ; 
 int /*<<< orphan*/  FW_LDST_CMD ; 
 int FW_LDST_CMD_ADDRSPACE_V (int /*<<< orphan*/ ) ; 
 int FW_LEN16 (struct fw_ldst_cmd) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_ldst_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_ldst_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_fwaddrspace_write(struct adapter *adap, unsigned int mbox,
			  u32 addr, u32 val)
{
	u32 ldst_addrspace;
	struct fw_ldst_cmd c;

	memset(&c, 0, sizeof(c));
	ldst_addrspace = FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_FIRMWARE);
	c.op_to_addrspace = cpu_to_be32(FW_CMD_OP_V(FW_LDST_CMD) |
					FW_CMD_REQUEST_F |
					FW_CMD_WRITE_F |
					ldst_addrspace);
	c.cycles_to_len16 = cpu_to_be32(FW_LEN16(c));
	c.u.addrval.addr = cpu_to_be32(addr);
	c.u.addrval.val = cpu_to_be32(val);

	return t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
}