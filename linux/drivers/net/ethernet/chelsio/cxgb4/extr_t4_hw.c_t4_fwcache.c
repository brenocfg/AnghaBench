#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fw_params_cmd {TYPE_1__* param; void* retval_len16; void* op_to_vfn; } ;
struct adapter {int /*<<< orphan*/  mbox; int /*<<< orphan*/  pf; } ;
typedef  enum fw_params_param_dev_fwcache { ____Placeholder_fw_params_param_dev_fwcache } fw_params_param_dev_fwcache ;
typedef  int /*<<< orphan*/  c ;
struct TYPE_2__ {void* val; void* mnem; } ;

/* Variables and functions */
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_CMD_WRITE_F ; 
 int FW_LEN16 (struct fw_params_cmd) ; 
 int /*<<< orphan*/  FW_PARAMS_CMD ; 
 int FW_PARAMS_CMD_PFN_V (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_CMD_VFN_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_FWCACHE ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_params_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_params_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_fwcache(struct adapter *adap, enum fw_params_param_dev_fwcache op)
{
	struct fw_params_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_vfn =
		cpu_to_be32(FW_CMD_OP_V(FW_PARAMS_CMD) |
			    FW_CMD_REQUEST_F | FW_CMD_WRITE_F |
			    FW_PARAMS_CMD_PFN_V(adap->pf) |
			    FW_PARAMS_CMD_VFN_V(0));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));
	c.param[0].mnem =
		cpu_to_be32(FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
			    FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_FWCACHE));
	c.param[0].val = cpu_to_be32(op);

	return t4_wr_mbox(adap, adap->mbox, &c, sizeof(c), NULL);
}