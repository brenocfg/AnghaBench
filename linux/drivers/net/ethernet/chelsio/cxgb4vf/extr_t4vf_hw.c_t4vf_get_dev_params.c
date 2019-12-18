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
typedef  void* u32 ;
struct dev_params {void* tprev; void* fwrev; } ;
struct TYPE_2__ {struct dev_params dev; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_FWREV ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_TPREV ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int t4vf_query_params (struct adapter*,int,void**,void**) ; 

int t4vf_get_dev_params(struct adapter *adapter)
{
	struct dev_params *dev_params = &adapter->params.dev;
	u32 params[7], vals[7];
	int v;

	params[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_FWREV));
	params[1] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_TPREV));
	v = t4vf_query_params(adapter, 2, params, vals);
	if (v)
		return v;
	dev_params->fwrev = vals[0];
	dev_params->tprev = vals[1];

	return 0;
}