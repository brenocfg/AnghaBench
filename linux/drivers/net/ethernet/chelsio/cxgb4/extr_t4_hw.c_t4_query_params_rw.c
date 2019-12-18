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
typedef  int u32 ;
struct fw_params_cmd {TYPE_1__* param; void* retval_len16; void* op_to_vfn; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;
typedef  void* __be32 ;
struct TYPE_2__ {void* val; void* mnem; } ;

/* Variables and functions */
 int EINVAL ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 int FW_LEN16 (struct fw_params_cmd) ; 
 int /*<<< orphan*/  FW_PARAMS_CMD ; 
 int FW_PARAMS_CMD_PFN_V (unsigned int) ; 
 int FW_PARAMS_CMD_VFN_V (unsigned int) ; 
 int /*<<< orphan*/  be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_params_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox_meat (struct adapter*,unsigned int,struct fw_params_cmd*,int,struct fw_params_cmd*,int) ; 

int t4_query_params_rw(struct adapter *adap, unsigned int mbox, unsigned int pf,
		       unsigned int vf, unsigned int nparams, const u32 *params,
		       u32 *val, int rw, bool sleep_ok)
{
	int i, ret;
	struct fw_params_cmd c;
	__be32 *p = &c.param[0].mnem;

	if (nparams > 7)
		return -EINVAL;

	memset(&c, 0, sizeof(c));
	c.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_PARAMS_CMD) |
				  FW_CMD_REQUEST_F | FW_CMD_READ_F |
				  FW_PARAMS_CMD_PFN_V(pf) |
				  FW_PARAMS_CMD_VFN_V(vf));
	c.retval_len16 = cpu_to_be32(FW_LEN16(c));

	for (i = 0; i < nparams; i++) {
		*p++ = cpu_to_be32(*params++);
		if (rw)
			*p = cpu_to_be32(*(val + i));
		p++;
	}

	ret = t4_wr_mbox_meat(adap, mbox, &c, sizeof(c), &c, sleep_ok);
	if (ret == 0)
		for (i = 0, p = &c.param[0].val; i < nparams; i++, p += 2)
			*val++ = be32_to_cpu(*p);
	return ret;
}