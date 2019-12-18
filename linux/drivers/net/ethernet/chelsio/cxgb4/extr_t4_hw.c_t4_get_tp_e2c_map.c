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
typedef  int u32 ;
struct adapter {int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_WARN (struct adapter*,char*,int,unsigned int) ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_TPCHMAP ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPS_CMN_CTL_A ; 
 int NUMPORTS_G (int /*<<< orphan*/ ) ; 
 int t4_query_params_ns (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int t4_get_tp_e2c_map(struct adapter *adapter, int pidx)
{
	unsigned int nports;
	u32 param, val = 0;
	int ret;

	nports = 1 << NUMPORTS_G(t4_read_reg(adapter, MPS_CMN_CTL_A));
	if (pidx >= nports) {
		CH_WARN(adapter, "TP E2C Channel Port Index %d >= Nports %d\n",
			pidx, nports);
		return 0;
	}

	/* FW version >= 1.16.44.0 can determine E2C channel map using
	 * FW_PARAMS_PARAM_DEV_TPCHMAP API.
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_TPCHMAP));
	ret = t4_query_params_ns(adapter, adapter->mbox, adapter->pf,
				 0, 1, &param, &val);
	if (!ret)
		return (val >> (8 * pidx)) & 0xff;

	return 0;
}