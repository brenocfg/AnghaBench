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
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_SCFGREV ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int t4_query_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 

int t4_get_scfg_version(struct adapter *adapter, u32 *vers)
{
	u32 scfgrev_param;
	int ret;

	scfgrev_param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
			 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_SCFGREV));
	ret = t4_query_params(adapter, adapter->mbox, adapter->pf, 0,
			      1, &scfgrev_param, vers);
	if (ret)
		*vers = 0;
	return ret;
}